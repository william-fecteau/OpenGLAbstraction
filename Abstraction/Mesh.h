#pragma once

#include "Resource.h"
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 _position;
	glm::vec2 _texCoords;
	glm::vec3 _normals;
};

class Mesh : public Resource
{
private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	VertexArray _va;
	VertexBuffer _vb;
	IndexBuffer _ib;
	VertexBufferLayout _vbl;

	//std::vector<Texture> textures;

public:
	Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals, std::vector<glm::vec2> texturePos = {});
	void LoadResource();
	void UnloadResource();
	void Render(const ShaderProgram& shader);
};