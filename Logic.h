#pragma once
#include "Storage.h"
#include "Shader.h"
#include "Input.h"
#include "Camera.h"
using namespace glm;

typedef unsigned int uint;


class Object
{
public:
	uint id;
	uint model_id;
	uint texture_id;

	bool draw = false;
	vec3 positionV{};
	vec3 rotationV{};
	vec3 scaleV{};

	float r = 0.0f;

	mat4 GetMatrix() { 
		mat4 matrix(1);
		matrix = translate(matrix, positionV); 
		matrix = scale(matrix, scaleV);
		matrix = rotate(matrix, radians(r), vec3(1.f, 0.0f, 0.0f));	//Rotate will broke the matrix if none of rotation directions will be defined
		return matrix;
	};
};

class Scene
{
public:
	uint id{};
	bool process = false;
	Storage<Object> objects{};
	Camera::params cameraParams;

	void Initialization(uint number_of_objects)
	{
		objects.Resize(number_of_objects);
	}

	uint CreateObject(bool draw, uint model_id, uint texture_id, vec3 init_position = {}, vec3 rotation = {}, vec3 scale = {1.0f, 1.0f, 1.0f})
	{
		Object* object = new Object;

		object->id = objects.Set(object);
		object->draw = draw;
		object->model_id = model_id;
		object->texture_id = texture_id;
		object->positionV = init_position;
		object->rotationV = rotation;
		object->scaleV = scale;

		return object->id;
	}

	Object* GetObject(uint id)
	{
		return objects.Get(id);
	}

	Camera::params* GetCamera()
	{
		return &cameraParams;
	}

};

class User
{
public:
	Input* input;
	vec3 rotationClamp{};
	float bruh = 0;

	Camera::params camera;

	float speed = 0.01f;
	float mouseSens = 0.2f;
	uint currentScene = 0;

	void Move();

	void SetRotation(vec3 rotation);
};

class Logic
{
	Storage<Scene> scenes;
	User user;
public:
	GLFWwindow* window;
	Input input;

	void Initialization(GLFWwindow* window, uint scenes_capacity)
	{
		user.input = &input;
		input.Init(window);
		this->window = window;
		scenes.Resize(scenes_capacity);
	}
	uint CreateScene(bool process, uint start_capacity);
	Scene* GetScene(uint id)
	{
		return scenes.Get(id);
	}

	void Execute();

	Storage<Scene> GetStorage() { return scenes; }
};
