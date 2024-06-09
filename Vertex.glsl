#version 460 core

layout (location = 0) in vec3 posIn;
layout (location = 1) in vec2 textureCoordsIn;
out vec2 textureCoordsFrag;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	textureCoordsFrag = textureCoordsIn;
	gl_Position = projection * view * transform * vec4(posIn, 1.0f);
}