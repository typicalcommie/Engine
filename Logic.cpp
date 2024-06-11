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
	vec3 data = input->GetData();

	camera.rotation -= vec3(data.x * mouseSens, data.y * -1.0f * mouseSens, data.x * mouseSens);

	if (camera.rotation.y > 89) camera.rotation.y = 89;
	else if (camera.rotation.y < -89) camera.rotation.y = -89;
	
	SetRotation(camera.rotation);

	if (input->GetKey(GLFW_KEY_LEFT_SHIFT)) speed = 0.1f;

	if (input->GetKey('W')) camera.position += rotationClamp * speed;
		
	if (input->GetKey('S')) camera.position -= rotationClamp * speed;
	
	if (input->GetKey('D')) camera.position += cross(rotationClamp, vec3(0.0f, 1.0f, 0.0f)) * speed;
	
	if (input->GetKey('A')) camera.position -= cross(rotationClamp, vec3(0.0f, 1.0f, 0.0f)) * speed;

	speed = 0.02f;
}

inline void User::SetRotation(vec3 rotation)
{
	if (rotation.y > 89) rotation.y = 89;
	else if (rotation.y < -89) rotation.y = -89;

	rotationClamp = rotation_calc(this->camera.rotation = rotation);
}

