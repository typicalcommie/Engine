#include "Texture.h"

void Texture::Create(std::string filename, int unit)
{

	uint alpha;
	uint lenght = filename.length();
	if (!memcmp(filename.data() + lenght - 4, ".png", 4))
		alpha = GL_RGBA;
	else alpha = GL_RGB;


	data = stbi_load(filename.data(), &width, &height, &clrChannels, 0);
	if (!data)
	{
		std::cout << "Can't load image.\n";
		return;
	}

	this->unit = unit;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, alpha, width, height, 0, alpha, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	free(data);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}
