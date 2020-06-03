#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int> indices, std::vector<glm::vec3> normals, std::vector<glm::vec2> texturePos)
{
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Vertex vertex;
		vertex._position = vertices[i];
		if(!texturePos.empty()) vertex._texCoords = texturePos[i];

		_vertices.push_back(vertex);
	}

	_indices = indices;

	_ib.SetData(&_indices[0], _indices.size());

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
	_ib.Bind();
	//glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
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

