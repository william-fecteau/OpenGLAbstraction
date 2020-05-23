#include "Window.h"

Window::Window(const std::string& name, const int width, const int height) : _name(name), _width(width), _height(height), _mouseXOffset(0), _mouseYOffset(0), _lastMouseX(_width / 2.0f), _lastMouseY(_height / 2.0f), _firstMouse(true)
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

	glEnable(GL_DEPTH_TEST);
	SetCallbackFunctions();

	_renderer = new Renderer();

	UpdateDeltaTime();

	_shouldClose = glfwWindowShouldClose(_window);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Render()
{
	UpdateDeltaTime();

	PollInput();

	_renderer->Render();

	glfwSwapBuffers(_window);
	glfwPollEvents();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shouldClose = glfwWindowShouldClose(_window);
}

void Window::UpdateDeltaTime()
{
	float currentFrame = (float)glfwGetTime();
	_deltaTime = currentFrame - _lastFrameTime;
	_lastFrameTime = currentFrame;
}


void Window::PollInput()
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_renderer->GetCamera().ProcessKeyboard(CameraMovement::FORWARD, _deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_renderer->GetCamera().ProcessKeyboard(CameraMovement::BACKWARD, _deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_renderer->GetCamera().ProcessKeyboard(CameraMovement::LEFT, _deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_renderer->GetCamera().ProcessKeyboard(CameraMovement::RIGHT, _deltaTime);
}



//Callbacks
void Window::SetCallbackFunctions()
{
	GLFWCallbackWrapper::SetWindow(this);
	glfwSetCursorPosCallback(_window, GLFWCallbackWrapper::MousePositionCallback);
	glfwSetKeyCallback(_window, GLFWCallbackWrapper::KeyboardCallback);
}

void Window::MousePositionCallback(double xpos, double ypos)
{
	if (_firstMouse)
	{
		_lastMouseX = (float)xpos;
		_lastMouseY = (float)ypos;
		_firstMouse = false;
	}

	_mouseXOffset = (float)xpos - _lastMouseX;
	_mouseYOffset = _lastMouseY - (float)ypos; //Inversé car la position y sur un écran est de haut vers bas
	_lastMouseX = (float)xpos;
	_lastMouseY = (float)ypos;

	_renderer->GetCamera().ProcessMouseMovement(_mouseXOffset, _mouseYOffset);
}

void Window::KeyboardCallback(int key, int scancode, int action, int mods)
{

}













//GLFWCallbackWrapper
void Window::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
	s_window->MousePositionCallback(positionX, positionY);
}

void Window::GLFWCallbackWrapper::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_window->KeyboardCallback(key, scancode, action, mods);
}


void Window::GLFWCallbackWrapper::SetWindow(Window* window)
{
	GLFWCallbackWrapper::s_window = window;
}

Window* Window::GLFWCallbackWrapper::s_window = nullptr;