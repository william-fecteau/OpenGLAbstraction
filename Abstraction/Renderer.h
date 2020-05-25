#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include "ICamera.h"
#include "ShaderProgram.h"


//Don't define DEBUG to be in PRODUCITON mode (No debug message in console)
#define DEBUG

#ifdef DEBUG
	#define GLCall(x) GLClearError();\
		x;\
		if(!GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
	#define GLCall(x) x
#endif

/**
*	Clears the OpenGL error flags
*/
void GLClearError();

//TODO: TEMPORARY HARDCODED SHADER PROGRAM
const std::string vertexPath = "C:\\Users\\willi\\Desktop\\Workspace\\OpenGLAbstraction\\shaders\\vertex.vs";
const std::string fragmentPath = "C:\\Users\\willi\\Desktop\\Workspace\\OpenGLAbstraction\\shaders\\fragment.fs";

/**
*	Loop through all the OpengGL error flags
*
*	@return Bool if there is an error
*/
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
	ICamera* _camera;
	ShaderProgram _shaderProgram;

public:
	Renderer();

	void Render() const;

	//Getters
	ICamera* GetCamera() const { return _camera; }
	const ShaderProgram& GetShaderProgram() const { return _shaderProgram; }
};

#endif