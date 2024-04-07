#pragma once
#include "Texture.h"
#include "Logic.h"
#include <thread>
//Sleep for milliseconds value
#define Sleep(mill) std::this_thread::sleep_for(std::chrono::milliseconds(mill));

class Engine
{
	GLFWwindow* window;
	ShaderProc proc;
public:

	Logic logic;
	bool Init();
	void Start();
};