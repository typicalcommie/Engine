#pragma once
#include "Texture.h"
#include "Storage.h"
#include "InputOutput.h"
#include "Logic.h"
#include "Camera.h"

#define _rcast(type, data) reinterpret_cast<type>(data)

const char path_to_models[] = "Data\\Models\\";

class Model
{
	uint id{};
	uint vertexArrayObject{};

	uint vertexBuffer{};
	uint vertexCount, vertexComplexity;

	uint layoutId{};

	static const uint offset = 4 * 4; //Magic, id, vertices count, complexity, indices count = 4 elements, 4 bytes each
public:

	void Create(uint id, float* vertices, uint complexity, uint count)
	{
		this->id = id;
		vertexCount = count;
		vertexComplexity = complexity;

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);
		
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, count * complexity * 4, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 20, (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 20, (void*)0);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

	}

	void Load(char* path)
	{
		//model.Create(5);
		char* file = IO::Read(path);

		uint* datai = _rcast(uint*, file);
		
		uint vertexCount = datai[2];
		uint complexity = datai[3];

		char* data = new char[(vertexCount) * 4] {};

		memcpy(data, file + 16, vertexCount * 4);
	}

	void Write(char* filename, uint size, uint id, float* vertices, uint* indices, uint verticescount, uint indicescount, uint complexity)
	{
		char* data{};

		if (!verticescount || !complexity || !vertices) return;

		char* fl = new char[sizeof(path_to_models) + size] {};

		memcpy(fl, path_to_models, sizeof(path_to_models));
		memcpy(fl + sizeof(path_to_models), filename, size);
		

		uint lenght = (verticescount * complexity * 4) + offset;

		data = new char[lenght] {};

		uint* datauint = _rcast(uint*, data);
		memcpy(data, "MDL ", 4);
		datauint[1] = id;
		datauint[2] = verticescount;
		datauint[3] = complexity;

		memcpy(data + offset, vertices, verticescount * 4);
		memcpy(data + offset + (verticescount * 4), indices, indicescount * 4);

		IO::Write(fl, data, lenght);

		_delete(fl);
		_delete(data);
	}

	void Prepare()
	{
		glBindVertexArray(vertexArrayObject);
	}

	uint GetVertexCount() { return vertexCount; }
};

class Graphics
{
	
	Storage<Model> models;
	Storage<Texture> textures;
	GLFWwindow* window;
	ShaderProc proc;
public:
	Camera camera;

	void Initialization()
	{
		models.Resize(100);
		textures.Resize(100);
	}

	void Draw(Storage<Scene> scenes)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Specifices what buffer will be cleared. GL_COLOR_BUFFER_BIT - to clear only color. There is also values for stencil and deep buffer, that can be cleared in one time if you set it with bitwise operator.
		glClearColor(0.0f, 0.3f, 0.2f, 0.0f);

		for (uint iterator = 0, i = 0, size = scenes.GetSize(); iterator < size; i++)
		{
			Scene* current = scenes.Get(i);
			if (current) 
			{
				iterator++;
				if (current->process)
					DrawScene(current);
			}
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void DrawScene(Scene* scene)
	{
		camera.SetParam(*scene->GetCamera());
		proc.SetUniformMatrix("view", camera.GetView());
		proc.SetUniformMatrix("projection", camera.GetProjection());
		for (uint iterator = 0, i = 0, size = scene->objects.GetSize(); iterator < size; i++)
		{
			Object* current = scene->objects.Get(i);
			if (current) 
			{
				iterator++;
				if (current->draw)	
					DrawObject(current);
			}
		}
	}

	void DrawObject(Object* object)
	{
		proc.SetUniformMatrix("transform", object->GetMatrix());
		models.Get(object->model_id)->Prepare();
		textures.Get(object->texture_id)->Bind();
		glDrawArrays(GL_TRIANGLES, 0, models.Get(object->model_id)->GetVertexCount());
	}

	uint SetModel(Model* model)
	{
		return models.Set(model);
	}

	uint SetTexture(Texture* texture)
	{
		return textures.Set(texture);
	}

	void SetWindow(GLFWwindow* window) { this->window = window; }
	ShaderProc* GetProc() { return &proc; }

};