#pragma once
#include "Shader.h"

class Camera
{

	mat4 projection;
	float fov{}; //Field of view
	float aspectRatio = 1.7f; //Basicly 1920 / 1080 = 1.777..., or any other resolution, you got it
	float near{};
	float far{};

public:
	struct params
	{
		float fov = 90; //Field of view
		float aspectRatio = 1.7; //Basicly 1920 / 1080 = 1.777..., or any other resolution, you got it
		float near = 0.1f; // !!! SHOULD NOT BE ZERO !!! IT'LL FUCK UP IF IT WILL BE.
		float far = 100.0f;
		vec3 position{};
		vec3 rotation{ 90, 0, 90 };
	};

	vec3 position{};
	vec3 rotation{ 90.0f, 0, 90.0f };
	vec3 sincos{};
	vec3 up = vec3(0.0f, 1.0f, 0.0f), right, front = vec3(0.0f, 0.0f, 1.0f);

	void  SetParam(params value);

	mat4  GetView();

	mat4  GetProjection();

};