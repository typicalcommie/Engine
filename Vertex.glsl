#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
out vec2 inp;

uniform float size;
uniform vec4 offset;
uniform mat4 transform;

void main()
{
	inp = tex;
	vec4 pos1 = vec4(pos, 1.0f);

	pos1 = transform  * pos1;

	

	gl_Position = pos1;
}