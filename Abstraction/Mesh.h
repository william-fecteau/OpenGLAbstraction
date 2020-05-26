#pragma once

#include "Resource.h"
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 _position;
	glm::vec2 _texCoords;
};

class Mesh : public Resource
{
private:
	std::vector<Vertex> _vertices;
	VertexArray _va;
	VertexBuffer _vb;
	VertexBufferLayout _vbl;

	//std::vector<Texture> textures;

public:
	Mesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec2> texturesPos);
	void LoadResource();
	void UnloadResource();
	void Render(const ShaderProgram& shader);
};