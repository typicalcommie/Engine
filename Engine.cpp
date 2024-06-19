#include "Engine.h"

vec2* winsize{};

void SizeChange(GLFWwindow* window, int x, int y)
{
	*winsize = {x, y};
	glViewport(0, 0, x, y);
}

bool Engine::Init()
{
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwInit();

	window = glfwCreateWindow(800, 600, "WElp!", 0, 0);
	winsize = &windowSize;
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
	
	//stbi_set_flip_vertically_on_load(true);

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

	Texture texture, bg;
	bg.Create("Data/Pics/back.jpg", 1);
	bg.Bind();
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

		1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 2.0f, 1.0f, 0.0f,

		1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 2.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 2.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 2.0f, 1.0f, 0.0f,

		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 2.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 2.0f, 1.0f, 1.0f
	};


	Model square;
	square.Create(1, vertices, 18);
	uint model = graphics.SetModel(&square);
	uint textr = graphics.SetTexture(&texture);
	uint back = graphics.SetTexture(&bg);

	uint scene = logic.CreateScene(true, 1);

	Camera::params *par = logic.GetScene(scene)->GetCamera();

	logic.GetScene(scene)->Initialization(6);
	logic.GetScene(scene)->CreateObject(true, model, textr, vec3(2.0f, 2.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
	logic.GetScene(scene)->CreateObject(true, model, back, vec3(-1.0f, -1.0f, 2.0f), vec3(0), vec3(0.5f, 0.5f, 0.5f));
	logic.GetScene(scene)->CreateObject(true, model, back, vec3(-10.0f, 2.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
	logic.GetScene(scene)->CreateObject(true, model, back, vec3(10.0f, -1.0f, -5.0f), vec3(0), vec3(0.5f, 0.5f, 0.5f));
	logic.GetScene(scene)->CreateObject(true, model, back, vec3(-5.0f, 2.0f, -20.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 0.3f, 0.3f));
	logic.GetScene(scene)->CreateObject(true, model, back, vec3(0.0f, -2.0f, 0.0f), vec3(0, 0, 0), vec3(50.0f, 0.05f, 50.0f));



	logic.GetScene(scene)->GetObject(5)->r = 90;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		//Camera::params::aspectRatio = windowSize.x / windowSize.y;
		logic.Execute();
		graphics.Draw(logic.GetStorage());
	}

	glfwTerminate();
}
