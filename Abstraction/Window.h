#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

/**
*	Abstraction of a GLFW Window
*/
class Window
{
private:
	//Pretty self-explanatory ;)
	int _width, _height;
	//If it should close on the next iteration
	bool _shouldClose;
	//Name of the window
	std::string _name;
	//Pointer to the GLFW Window
	GLFWwindow* _window;

public:
	/**
	*	Create a window and associate it with an opengl context
	*
	*	@param name Name of the window
	*	@param width Width of the window
	*	@param height Height of the window
	*/
	Window(const std::string& name, const int width, const int height);

	/**
	*	Free the GLFW window data
	*/
	~Window();

	/**
	*	Render method that can be overwritten
	*/
	virtual void Render();

	/**
	*	Input polling that can be overwritten
	*/
	virtual void PollInput();

	/**
	*	Getter on _shouldClose
	*/
	const bool ShouldClose() const { return _shouldClose; }
};