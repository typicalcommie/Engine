#include "Logic.h"

vec3 rotation_calc(vec3 rotationDegrees)
{
	vec3 result = radians(rotationDegrees);
	return vec3(cos(result.x), sin(result.y), sin(result.z));
}

uint Logic::CreateScene(bool process, uint start_capacity)
{
	Scene* scene = new Scene;
	scene->process = process;
	scene->Initialization(start_capacity);
	return scenes.Set(scene);
}

void Logic::Execute()
{
	input.Execute();

	user.Move();
	Camera::params* par = scenes.Get(user.currentScene)->GetCamera();
	*par = user.camera;

} 

void User::Move()
{

	SetRotation(vec3(90.1f, 0.0f, 90.0f));
	camera.position = vec3(0.0f, 0.0f, -5.0f);

	if (input->GetKey('W')) camera.position += rotationClamp * speed;
		
	if (input->GetKey('S')) camera.position -= rotationClamp * speed;
	
	if (input->GetKey('D')) camera.position += cross(rotationClamp, vec3(0.0f, 1.0f, 0.0f)) * speed;
	
	if (input->GetKey('A')) camera.position -= cross(rotationClamp, vec3(0.0f, 1.0f, 0.0f)) * speed;
}

inline void User::SetRotation(vec3 rotation)
{
	camera.rotation = rotation;

	vec3 dat;

	rotationClamp = radians(rotation);
	dat.x = cos(rotationClamp.x);
	dat.y = sin(rotationClamp.y);
	dat.z = sin(rotationClamp.z);
}

