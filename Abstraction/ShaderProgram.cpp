#include "ShaderProgram.h"
#include "Renderer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, const char* geometryPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	GLCall(vertex = glCreateShader(GL_VERTEX_SHADER));
	GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
	GLCall(glCompileShader(vertex));
	CheckCompileErrors(vertex, "VERTEX");
	// fragment Shader
	GLCall(fragment = glCreateShader(GL_FRAGMENT_SHADER));
	GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
	GLCall(glCompileShader(fragment));
	CheckCompileErrors(fragment, "FRAGMENT");
	// if geometry shader is given, compile geometry shader
	unsigned int geometry;
	if (geometryPath != nullptr)
	{
		const char* gShaderCode = geometryCode.c_str();
		GLCall(geometry = glCreateShader(GL_GEOMETRY_SHADER));
		GLCall(glShaderSource(geometry, 1, &gShaderCode, NULL));
		GLCall(glCompileShader(geometry));
		CheckCompileErrors(geometry, "GEOMETRY");
	}
	// shader Program
	GLCall(_id = glCreateProgram());
	GLCall(glAttachShader(_id, vertex));
	GLCall(glAttachShader(_id, fragment));
	if (geometryPath != nullptr)
	{
		GLCall(glAttachShader(_id, geometry));
	}

	GLCall(glLinkProgram(_id));
	CheckCompileErrors(_id, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));
	if (geometryPath != nullptr)
	{
		GLCall(glDeleteShader(geometry));
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


//SETTERS
void ShaderProgram::SetBool(const std::string& name, bool value) const
{
	GLCall(glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value));
}

void ShaderProgram::SetInt(const std::string& name, int value) const
{
	GLCall(glUniform1i(glGetUniformLocation(_id, name.c_str()), value));
}

void ShaderProgram::SetFloat(const std::string& name, float value) const
{
	GLCall(glUniform1f(glGetUniformLocation(_id, name.c_str()), value));
}

void ShaderProgram::SetVec2(const std::string& name, const glm::vec2& value) const
{
	GLCall(glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]));
}

void ShaderProgram::SetVec2(const std::string& name, float x, float y) const
{
	GLCall(glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y));
}

void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& value) const
{
	GLCall(glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]));
}

void ShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const
{
	GLCall(glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z));
}

void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& value) const
{
	GLCall(glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]));
}

void ShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	GLCall(glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w));
}

void ShaderProgram::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	GLCall(glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	GLCall(glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::CheckCompileErrors(GLuint shader, std::string type) const
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
		if (!success)
		{
			GLCall(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		GLCall(glGetProgramiv(shader, GL_LINK_STATUS, &success));
		if (!success)
		{
			GLCall(glGetProgramInfoLog(shader, 1024, NULL, infoLog));
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}