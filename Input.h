#pragma once

#include "Shader.h"

class Input
{
	GLFWwindow* window;
	void Init(GLFWwindow* window) { this->window = window; }

	mat4 InputProc()
	{
		vec3 pos{};
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
			pos.y += 0.05f;
		}
		return translate(mat4(1), pos);
	}


};