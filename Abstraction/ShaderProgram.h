#pragma once

#include <string>

class ShaderProgram
{
private:
	unsigned int _id;

public:
	ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	void Bind() const;
	void Unbind() const;

	const unsigned int GetId() const { return _id; };

private:
	void CompileShader(unsigned int shader, const char* source) const;
};

