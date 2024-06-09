#pragma once

#include "Shader.h"

class Input
{
	vec2 mouse{};
	float scroll{};
	vec3 data{};
public:
	GLFWwindow* window;
	void Init(GLFWwindow* window);

	inline bool Key(char key) { glfwGetKey(window, key); }
	vec2 GetMouse();
	float GetScroll();
	vec3 GetData();
	bool GetKey(uint key);
	void Execute();
};