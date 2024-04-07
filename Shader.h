#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace glm;
typedef unsigned int uint;

class Layout
{
	uint id;
public:
	//stride - is count of values in a row.
	void Create(uint id, uint size, uint stride, uint offset) { this->id = id; glVertexAttribPointer(id, size, GL_FLOAT, false, stride * 4, (void*)(offset * 4)); }
	void Enable() { glEnableVertexAttribArray(id); }
	void Disable() { glDisableVertexAttribArray(id); }
	uint GetId() { return id; }
	
};

class VertexObjectArray
{
	uint id{};

public:

	VertexObjectArray() { glGenVertexArrays(1, &id); }

	void inline Create() { if(!id) glGenVertexArrays(1, &id); }

	void inline Bind() { glBindVertexArray(id); }

	void inline Delete() { glDeleteVertexArrays(1, &id); }

};

class Index
{
	uint id;

public:

	void Create() { glGenBuffers(1, &id); }
	void Set(uint* data, uint size) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); };
	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
};

class VertexObject
{
	uint id{};
	uint complexity{};
	uint size{};
	bool allocated = false;
public:

	void Create(uint complexity)
	{
		this->complexity = complexity;
		glGenBuffers(1, &id);
	}

	void Create(float* data, uint size, uint complexity);

	void Set(float* data, uint size)
	{
		this->size = size;
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size * complexity, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		allocated = true;
	}

	void Update(float* data, uint offset, uint size)
	{
		if (!allocated)
			return;
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(GL_ARRAY_BUFFER, offset * complexity, size * complexity, data);
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }


};

//Made it nicer to use.
enum vertex_type
{
	VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader
{
	uint id;
	vertex_type type;
	bool Compiled();
public:
	bool Create(vertex_type type, char* path);

	uint GetID() { return id; }
	vertex_type GetType() { return type; }
};

class ShaderProc
{
	uint id;

public:
	void Create()
	{
		id = glCreateProgram();
	}

	void Attach(Shader shader)
	{
		glAttachShader(id, shader.GetID());
	}

	bool Link()
	{
		glLinkProgram(id);
		int status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (!status)
		{
			char log[512]{};
			glGetProgramInfoLog(id, 512, 0, log);
			std::cout << "Shader Program linking has failed: " << log << std::endl;
			return false;
		}
		return true;
	}

	void Use()
	{
		glUseProgram(id);
	}

	void SetUniformFloat(std::string name, float value);
	void SetUniformInteger(std::string name, int value);
	void SetUniformVector(std::string name, glm::vec4 vec) { glUniform4fv(glGetUniformLocation(id, name.data()), 1, glm::value_ptr(vec)); }
	void SetUniformMatrix(std::string name, glm::mat4 mat) { glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, false, glm::value_ptr(mat)); }
};
