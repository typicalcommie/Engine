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
	Logic logic;

public:
	bool Init();
	void Start();
};