#include "Renderer.h"
#include <iostream>

Renderer::Renderer(ICamera* camera, glm::mat4* projection) : _shaderProgram(vertexPath, fragmentPath)
{
	_camera = camera;

	//Projection matrix
	if (projection == nullptr)
	{
		projection = &glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	}
	
	_shaderProgram.Bind();
	_shaderProgram.SetMat4("projection", *projection);
}

Renderer::~Renderer()
{
	delete _camera;
}

void Renderer::Render() const
{
	//View matrix
	glm::mat4 view = _camera->GetViewMatrix();

	_shaderProgram.Bind();
	_shaderProgram.SetMat4("view", view);

	for (Mesh* mesh : _meshToRender)
	{
		mesh->Render(_shaderProgram);
	}

	_meshToRender.clear();
}

void Renderer::AddToRender(Mesh& mesh)
{
	_meshToRender.push_back(&mesh);
}

void Log(const char* message, const char* file, int line)
{
	std::cout << "[Log] " << message  << " " <<  file << ":" << line << std::endl;
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