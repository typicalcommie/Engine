#pragma once
#include "Storage.h"
#include "Shader.h"
#include "Input.h"
using namespace glm;

typedef unsigned int uint;


class Object
{
public:
	uint id;
	uint model_id;
	uint texture_id;

	bool draw = false;
	vec3 position{};
	mat4 rotation{1};
	mat4 scale{1};

	void Create(uint id, uint modelid, uint textureid) { id = id; model_id = modelid; texture_id = textureid; };

	void SetPosition(vec3 pos) { position = pos; }
	void AddPosition(vec3 pos) { position += pos; }
	void DrawState(bool state) { draw = state; };
	mat4 GetMatrix() { return rotation * scale * translate(mat4(), position); };
};

class Scene
{
public:
	uint id{};
	bool process = false;
	Storage<Object> objects{};
	
	uint CreateObject()
	{
		Object object;
		return objects.Set(object);
	}

};

class Logic
{
public:
	Storage<Scene> scenes;
	Input input;

	void Initialization(uint number_of_scenes)
	{
		scenes.Resize(number_of_scenes);
		for (uint i = 0; i < number_of_scenes; i++)
		{
			Scene scene;
			scene.id = i;
			scenes.Set(scene);
		}
	}
};
