#include "Engine.h"

void SizeChange(GLFWwindow* window, int x, int y)
{
	glViewport(0, 0, x, y);
}

bool Engine::Init()
{
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwInit();

	window = glfwCreateWindow(800, 600, "WElp!", 0, 0);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	graphics.SetWindow(window);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		glfwTerminate();
		return false;
	}

	//Defining function for resize call
	glfwSetFramebufferSizeCallback(window, SizeChange);

	glViewport(0, 0, 800, 600);
	
	//Blend setup
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	graphics.Initialization();
	
	Shader vertex, fragment;
	vertex.Create(VERTEX, (char*)"Vertex.glsl");
	fragment.Create(FRAGMENT, (char*)"Fragment.glsl");
	

	ShaderProc* proc = graphics.GetProc();
	proc->Create();
	proc->Attach(vertex);
	proc->Attach(fragment);
	proc->Link();

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	return true;
}


void Engine::Start()
{
	graphics.GetProc()->Use();

	Texture texture;
	texture.Create((char*)"Data/Pics/desu~.jpg", 1);
	texture.Bind();
	
	Logic logic;
	logic.Initialization(window, 1);
	logic.input.Init(window);

	float vertices[] =
	{
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f,	//front, left low
		-1.0f, 1.0f, 0.0f,   0.0f, 0.0f,	// front, left high
		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,		// front, right high

		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f,	//front, left low
		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,		//front, right high
		1.0f, -1.0f, 0.0f,  1.0f, 1.0f,		//front, right low

		1.0f, 1.0f, 2.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,  1.0f, 1.0f,	//right side

		1.0f, -1.0f, 2.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 2.0f,  0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,  1.0f, 1.0f,

		-1.0f, 1.0f, 2.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f,	//left side

		-1.0f, -1.0f, 2.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 2.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f
	};

	Model square;
	square.Create(1, vertices, 5, 18);
	uint model = graphics.SetModel(&square);
	uint textr = graphics.SetTexture(&texture);

	uint scene = logic.CreateScene(true, 1);

	Camera::params *par = logic.GetScene(scene)->GetCamera();

	logic.GetScene(scene)->Initialization(6);
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(2.0f, 2.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(-1.0f, -1.0f, 2.0f), vec3(0), vec3(0.5f, 0.5f, 0.5f));
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(-10.0f, 2.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(10.0f, -1.0f, -5.0f), vec3(0), vec3(0.5f, 0.5f, 0.5f));
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(-5.0f, 2.0f, -20.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(5.0f, -1.0f, -20.0f), vec3(0), vec3(0.5f, 0.5f, 0.5f));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		logic.Execute();
		graphics.Draw(logic.GetStorage());
	}

	glfwTerminate();
}
