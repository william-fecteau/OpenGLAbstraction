#include "Renderer.h"
#include "Image.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera3D.h"
#include <iostream>

Renderer::Renderer() : _shaderProgram(vertexPath, fragmentPath)
{
	_camera = new Camera3D();

	//Projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	//Uniform stuff 
	_shaderProgram.Bind();
	_shaderProgram.SetMat4("projection", projection);
}

void Renderer::Render() const
{
	//View matrix
	glm::mat4 view = _camera->GetViewMatrix();

	_shaderProgram.Bind();
	_shaderProgram.SetMat4("view", view);
}

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}