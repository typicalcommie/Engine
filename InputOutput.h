#pragma once
#include <fstream>

typedef unsigned int uint;

namespace IO
{
	static void Write(char* path, char* data, uint size)
	{
		if (!data || !path) return;
		std::ofstream file;

		file.open(path, std::ios::binary);
		if (!file.is_open()) return;
		file.write(data, size);
		file.close();
	}

	static char* Read(char* path)
	{
		char* data{};
		uint lenght{};

		if (!path) return 0;

		std::ifstream file;

		file.open(path, std::ios::binary | std::ios::ate);
		if (!file.is_open()) return 0;
		lenght = file.tellg();
		file.seekg(0, std::ios::beg);
		if (!lenght) return 0;
		data = new char[lenght] {};
		file.read(data, lenght);
		file.close();

		return data;
	}
}