#pragma once
#include "Texture.h"
#include "Logic.h"
#include "Graphics.h"
#include "Camera.h"
#include <thread>
//Sleep for milliseconds value
#define Sleep(mill) std::this_thread::sleep_for(std::chrono::milliseconds(mill));

class Engine
{
	GLFWwindow* window;

public:
	Graphics graphics;
	Logic logic;
	bool Init();
	void Start();
};