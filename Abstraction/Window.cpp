#include "Window.h"

Window::Window(const std::string& name, const int width, const int height) : _name(name), _width(width), _height(height)
{
	//Initializing glfw with openGL 3.3 core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating a window and associating it with the opengl context
	_window = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

	if (_window == NULL)
	{
		glfwTerminate();
		//TODO: Error handling
	}
	glfwMakeContextCurrent(_window);

	//Loading glad 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//TODO: Error handling
	}

	_shouldClose = glfwWindowShouldClose(_window);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Render()
{
	PollInput();

	glfwSwapBuffers(_window);
	glfwPollEvents();

	_shouldClose = glfwWindowShouldClose(_window);
}

void Window::PollInput()
{
	//Input handling
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);
}