#include "ShaderProgram.h"
#include "Renderer.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int vertexShader;
	GLCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));

	unsigned int fragmentShader;
	GLCall(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

	CompileShader(vertexShader, vertexShaderSource.c_str());
	CompileShader(fragmentShader, fragmentShaderSource.c_str());
	
	GLCall(_id = glCreateProgram());
	GLCall(glAttachShader(_id, vertexShader));
	GLCall(glAttachShader(_id, fragmentShader));
	GLCall(glLinkProgram(_id));

	int  success;
	char infoLog[512];
	glGetShaderiv(_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(_id, 512, nullptr, infoLog);
		//ERROR HANDLING
	}

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
}

void ShaderProgram::CompileShader(unsigned int shader, const char* source) const
{
	GLCall(glShaderSource(shader, 1, &source, nullptr));
	GLCall(glCompileShader(shader));

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		//TODO: ERROR HANDLING
	}
}

void ShaderProgram::Bind() const
{
	GLCall(glUseProgram(_id));
}

void ShaderProgram::Unbind() const
{
	GLCall(glUseProgram(0));
}