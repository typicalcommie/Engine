#include "Input.h"

double oldMouseX{}, oldMouseY{};
double accelMouseX{}, accelMouseY{};
bool agedMouse = true;

double accelScrollY{};
bool agedScroll = true;

void MouseProc(GLFWwindow* window, double x, double y)
{ 

	accelMouseX = oldMouseX - x; accelMouseY = oldMouseY - y;

	oldMouseX = x; oldMouseY = y;
	agedMouse = false;
}

void ScrollProc(GLFWwindow* window, double x, double y)
{
	accelScrollY = y;
	agedScroll = false;
}

void Input::Init(GLFWwindow* window)
{
	this->window = window;
	glfwSetCursorPosCallback(window, MouseProc);
	glfwSetScrollCallback(window, ScrollProc);
}

vec2 Input::GetMouse()
{
	if (!agedMouse) 
		mouse = { accelMouseX, accelMouseY };
	else 
		mouse = {0.0f, 0.0f};

	agedMouse = true;
	return mouse;
}

float Input::GetScroll()
{
	if (!agedScroll)
		scroll = accelScrollY;
	else scroll = 0;
	agedScroll = true;
	return scroll;
}

bool Input::GetKey(uint key)
{
	return glfwGetKey(window, key);
}

vec3 Input::GetData()
{
	return data;
}

void Input::Execute()
{
	data = vec3(GetMouse(), GetScroll());
}
