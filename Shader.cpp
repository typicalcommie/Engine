#include "Shader.h"

bool Shader::Compiled()
{
	int compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		char log[512]{};
		glGetShaderInfoLog(id, 512, 0, log);
		std::cout << "Compilation in shader has failed.\nError log:\n" << log << std::endl;
		glfwTerminate();
		return false;
	}
	return true;
}

bool Shader::Create(vertex_type type, char* path)
{
	this->type = type;
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		std::cout << "Can't find file at path: " << path << std::endl;
		return false;
	}
	uint lenght = file.tellg();
	if (lenght == 0)
	{
		std::cout << "Can't read file at path: " << path << std::endl;
		return false;
	}
	char* data = new char[lenght + 1] {};

	file.seekg(0, std::ios::beg);
	file.read(data, lenght);

	id = glCreateShader(type);
	glShaderSource(id, 1, &data, 0);
	glCompileShader(id);
	return Compiled();
}

void ShaderProc::SetUniformFloat(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(id, name.data()), value);
}

void ShaderProc::SetUniformInteger(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.data()), value);
}
