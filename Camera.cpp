#include "Camera.h"

//float Camera::params::aspectRatio = 1.777f;

//void Camera::SetParam(params value)
//{
//	this->fov = radians(value.fov);
//	this->aspectRatio = value.aspectRatio;
//	this->near = value.near;
//	this->far = value.far;
//	position = value.position;
//	rotation = value.rotation;
//}
//
//mat4 Camera::GetView()
//{
//	sincos.x = cos(radians(rotation.x)) * cos(radians(rotation.y));	//HOLY SHIT. IT'S GENIUS. By taking cos of y axis, i restrict x and z axis, so i can look staight up!
//	//When i look up, i looking at 90 degrees by y axis, which is 1.0 by sin, but by cos it's 0.0.
//	sincos.y = sin(radians(rotation.y));
//	sincos.z = sin(radians(rotation.z)) * cos(radians(rotation.y));
//
//	return lookAt(position, position + (sincos * vec3(1.0f, 1.0f, 1.0f)), up);
//}
//
//mat4 Camera::GetProjection()
//{
//	return projection = perspective(fov, aspectRatio, near, far);
//}