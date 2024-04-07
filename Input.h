#pragma once

#include "Shader.h"

class Input
{
public:
	GLFWwindow* window;
	void Init(GLFWwindow* window) { this->window = window; }

	vec3 pos;

	vec3 InputProc()
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pos.y += 0.05f;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			pos.y += -0.05f;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			pos.x += -0.05f;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			pos.x += 0.05f;
		}
		return pos;
	}


};