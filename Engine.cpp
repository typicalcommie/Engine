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
	
	
	Shader vertex, fragment;


	vertex.Create(VERTEX, (char*)"Vertex.glsl");
	fragment.Create(FRAGMENT, (char*)"Fragment.glsl");
	proc.Create();
	proc.Attach(vertex);
	proc.Attach(fragment);
	proc.Link();

	return true;
}


void Engine::Start()
{
	VertexObjectArray vao;
	vao.Create();
	vao.Bind();

	VertexObject triangle;

	float vertices[] =
	{
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,  1.0f, 1.0f
	};

	triangle.Create(vertices, 4, 5);

	Index index;
	index.Create();
	uint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	index.Set(indices, 24);

	index.Bind();
	triangle.Bind();
	Layout vert, tex;

	vert.Create(0, 3, 5, 0);
	vert.Enable();
	tex.Create(1, 2, 5, 3);
	tex.Enable();

	Texture texture, texture1;
	int i = 0, a = 1;

	texture.Create((char*)"Data/Pics/desu~.jpg", 1);
	texture1.Create((char*)"Data/Pics/st.jpg", 0);

	texture.Bind();
	texture1.Bind();
	proc.Use();
	proc.SetUniformInteger("first", 0);
	proc.SetUniformInteger("second", 1);

	float size = 0.3f;
	glfwSwapInterval(1);
	vao.Bind();

	vec4 pos = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	mat4 trans{1};
	mat4 scl = scale(mat4(1), vec3(0.1, 0.1, 0.1));

	Logic logic;
	logic.Initialization(1);
	logic.input.Init(window);

	while (!glfwWindowShouldClose(window))
	{
		trans = mat4(1);
		trans *= scl;
		//trans = rotate(trans, radians(1.f), vec3(1, 1, 0));
		trans = translate(trans, logic.input.InputProc());
		//
		proc.SetUniformFloat("size", size);
		proc.SetUniformMatrix("transform", trans);
		glClear(GL_COLOR_BUFFER_BIT); //Specifices what buffer will be cleared. GL_COLOR_BUFFER_BIT - to clear only color. There is also values for stencil and deep buffer, that can be cleared in one time if you set it with bitwise operator.
		glClearColor(0.0f, 0.3f, 0.2f, 0.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}