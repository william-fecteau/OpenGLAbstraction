#include "Window.h"
#include <iostream>

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const std::string vertexPath = "C:\\Users\\willi\\Desktop\\Workspace\\OpenGLAbstraction\\shaders\\vertex.vs";
const std::string fragmentPath = "C:\\Users\\willi\\Desktop\\Workspace\\OpenGLAbstraction\\shaders\\fragment.fs";

int main()
{
	Window window("Test2", 800, 600);

	ShaderProgram shaderProgram(vertexPath, fragmentPath);

	//Cube vertices
	float vertices[] = 
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//IndexBuffer ib(indices, 6);

	Image img("C:\\Users\\willi\\Downloads\\container.jpg");
	Texture tex(img);

	Image img2("C:\\Users\\willi\\Downloads\\awesomeface.png", true);
	Texture tex2(img2);

	VertexArray va;
	VertexBuffer vb(vertices, sizeof(vertices) * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//Matrix stuff
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	//Uniform stuff 
	shaderProgram.Bind();
	shaderProgram.SetMat4("projection", projection);
	shaderProgram.SetInt("tex", 0);
	shaderProgram.SetInt("tex2", 1);

	glfwSetInputMode(window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Render loop
	while (!window.ShouldClose())
	{
		tex.Bind(0);
		tex2.Bind(1);

		//Model matrix
		glm::mat4 model = glm::mat4(1.0f);

		//View matrix
		glm::mat4 view = window.GetCamera().GetViewMatrix();

		//Uniform stuff
		shaderProgram.Bind();
		shaderProgram.SetMat4("model", model);
		shaderProgram.SetMat4("view", view);

		va.Bind();
		//ib.Bind();

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		window.Render();
	}
}