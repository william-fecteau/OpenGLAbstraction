#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec2> texturesPos, std::vector<glm::vec3> normals)
{
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Vertex vertex;
		vertex._position = vertices[i];
		if(!texturesPos.empty()) vertex._texCoords = texturesPos[i];
		if(!normals.empty()) vertex._normals = normals[i];

		_vertices.push_back(vertex);
	}

	_vb.SetData(&_vertices[0], _vertices.size() * 8 * sizeof(float));
	_vbl.Push<float>(3);
	_vbl.Push<float>(2);
	_vbl.Push<float>(3);
	_va.AddBuffer(_vb, _vbl);
}

void Mesh::Render(const ShaderProgram& shader)
{
	shader.Bind();
	_va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
}

void Mesh::LoadResource()
{
	if (!_loaded)
	{
		//READ DATA FROM PATH INSTEAD FROM CTOR
		Resource::LoadResource();

	}
}

void Mesh::UnloadResource()
{
	if (_loaded)
	{
		Resource::UnloadResource();

	}
}

