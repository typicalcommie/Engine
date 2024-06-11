#pragma once
#include "Shader.h"

class Camera
{

	mat4 projection;
	float fov{}; //Field of view
	float aspectRatio{}; //Basicly 1920 / 1080 = 1.777..., or any other resolution, you got it
	float near{};
	float far{};

public:
	struct params
	{
		float fov = 45; //Field of view
		float aspectRatio = 1.777f; //Basicly 1920 / 1080 = 1.777..., or any other resolution, you got it
		float near = 0.1f; // !!! SHOULD NOT BE ZERO !!! IT'LL FUCK UP IF IT WILL BE.
		float far = 100.0f;
		vec3 position{};
		vec3 rotation{ 90, 0, 90 };
	};

	vec3 position{};
	vec3 rotation{90.0f, 0, 90.0f};
	vec3 sincos{};
	vec3 up = vec3(0.0f, 1.0f, 0.0f), right , front = vec3(0.0f, 0.0f, 1.0f);
	void SetParam(params value)
	{
		this->fov = radians(value.fov);
		this->aspectRatio = value.aspectRatio;
		this->near = value.near;
		this->far = value.far;
		position = value.position;
		rotation = value.rotation;
	}

	inline mat4 GetProjection()
	{
		return projection = perspective(fov, aspectRatio, near, far);
	}

	mat4 GetView()
	{
		sincos.x = cos(radians(rotation.x)) * cos(radians(rotation.y));	//HOLY SHIT. IT'S GENIUS. By taking cos of y axis, i restrict x and z axis, so i can look staight up!
																		//When i look up, i looking at 90 degrees by y axis, which is 1.0 by sin, but by cos it's 0.0.
		sincos.y = sin(radians(rotation.y));
		sincos.z = sin(radians(rotation.z)) * cos(radians(rotation.y));

		return lookAt(position, position + (sincos * vec3(1.0f, 1.0f, 1.0f)), up);
	}
};