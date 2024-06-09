#pragma once

typedef unsigned int uint;

class Text
{
	uint size;
	uint lenght;

	char* data;

public:

	uint Set(char* data)
	{
		if (!data) return 0;
		 
		for (uint i = 0; data[i] != 0; i++);
	}

};