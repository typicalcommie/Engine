#pragma once
#include "stb_image.h"
#include "Shader.h"

class Texture
{
	uint id{};
	int unit{};
	int width{}, height{}, clrChannels{};
	unsigned char* data{};

public:

	void Create(std::string filename, int unit);

	void Bind();
};