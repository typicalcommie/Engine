#version 460 core

in vec2 inp;
out vec4 color;

uniform sampler2D first;
uniform sampler2D second;

void main()
{
	color = mix(texture(second, inp), texture(first, inp), 0.5f);
	color.a = 0.1f;

}