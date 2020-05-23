#pragma once

#include "Renderer.h"

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
	//Time tracking
	float _deltaTime, _lastFrameTime;
	//Mouse tracking
	float _mouseXOffset, _mouseYOffset, _lastMouseX, _lastMouseY;
	bool _firstMouse;
	//The renderer
	Renderer* _renderer;


	/**
	*	Nested class that keeps a static instance of this window -> It is used to 
	*   access private attributes of this Window class and still be able to link callback to GLFW window
	*/
	class GLFWCallbackWrapper
	{
	private:
		static Window* s_window;
	public:
		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;

		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void SetWindow(Window* window);
	};

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

	//Getters
	const bool ShouldClose() const { return _shouldClose; }
	GLFWwindow* GetGLFWWindow() const { return _window; }
	const float GetDeltaTime() const { return _deltaTime; }
	const float GetMouseXOffset() const { return _mouseXOffset; }
	const float GetMouseYOffset() const { return _mouseYOffset; }
	Renderer& GetRenderer() const { return *_renderer; }

private:
	/**
	*	Update delta time
	*/
	void UpdateDeltaTime();

	//Callbacks
	void SetCallbackFunctions();
	void MousePositionCallback(double xpos, double ypos);
	void KeyboardCallback(int key, int scancode, int action, int mods);
	void PollInput();
};