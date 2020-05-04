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


const std::string vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"	TexCoord = aTexCoord;\n"
"}\0";

const std::string fragmentShaderSource =
"#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D tex;\n"
"uniform sampler2D tex2;\n"
"void main()\n"
"{\n"
"	FragColor = mix(texture(tex, TexCoord), texture(tex2, TexCoord), 0.2);\n"
"}\0";

int main()
{
	Window window("Test2", 800, 600);

	ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);

	float vertices[] =
	{
		//Pos                 //Tex
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,	
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3 
	};

	IndexBuffer ib(indices, 6);

	Image img("C:\\Users\\willi\\Downloads\\container.jpg");
	Texture tex(img);

	Image img2("C:\\Users\\willi\\Downloads\\awesomeface.png", true);
	Texture tex2(img2);

	VertexArray va;
	VertexBuffer vb(vertices, 20 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	//Uniform stuff 
	shaderProgram.Bind();
	glUniform1i(glGetUniformLocation(shaderProgram.GetId(), "tex"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram.GetId(), "tex2"), 1);
	unsigned int transformLoc = glGetUniformLocation(shaderProgram.GetId(), "transform");


	//Render loop
	while (!window.ShouldClose())
	{
		window.PollInput();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		tex.Bind(0);
		tex2.Bind(1);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		shaderProgram.Bind();
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		window.Render();
	}
}