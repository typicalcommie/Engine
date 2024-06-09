#version 460 core

in vec2 textureCoordsFrag;
out vec4 color;

uniform sampler2D first;

void main()
{
	color = texture(first, textureCoordsFrag);
//	color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}