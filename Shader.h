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

class Index
{
	uint id{};

public:

	void Create() { glGenBuffers(1, &id); }
	void Set(uint* data, uint size) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); };
	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
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
