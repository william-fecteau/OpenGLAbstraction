#include "Window.h"
#include <iostream>

#include "Texture.h"
#include "Image.h"
#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <istream>
#include <vector>

#include <string>
#include <vector>
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"

const float rawData[] = 
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

	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
};

const float rawDataNoTexture[] =
{
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,  
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f,  
	-0.5f, -0.5f, -0.5f, 

	-0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f,  
	 0.5f,  0.5f,  0.5f,  
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 

	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f,  
	-0.5f, -0.5f, -0.5f,  
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f,  

	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f,  

	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f,  
	-0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f, -0.5f,  

	-0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f, 
};

std::string ReadFile(const std::string& filePath) 
{
	std::ifstream inFile;
	inFile.open(filePath);

	std::stringstream strStream;
	strStream << inFile.rdbuf();

	return strStream.str();
}

const std::vector<std::string> Split(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}


int main()
{
	Window window("Test2", 800, 600);

	std::vector<glm::vec3> verticesVec;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texturesPos;
	std::vector<unsigned int> indices;

	std::ifstream file;
	file.open("C:\\Users\\willi\\Desktop\\Workspace\\OpenGLAbstraction\\cube.obj");
	std::string line;
	while (std::getline(file, line))
	{
		std::string data = line.substr(0, 2);

		//Vertex
		if (data == "v ")
		{
			std::vector<std::string> splittedData = Split(line, ' ');
			verticesVec.push_back(glm::vec3(stof(splittedData[1]), stof(splittedData[2]), stof(splittedData[3])));
		}
		//Textures
		else if (data == "vt")
		{
			std::vector<std::string> splittedData = Split(line, ' ');
			texturesPos.push_back(glm::vec2(stof(splittedData[1]), stof(splittedData[2])));

		}
		//Normals
		else if (data == "vn")
		{
			std::vector<std::string> splittedData = Split(line, ' ');
			normals.push_back(glm::vec3(stof(splittedData[1]), stof(splittedData[2]), stof(splittedData[3])));
		}
		//Indices
		else if (data == "f ")
		{
			std::vector<std::string> splittedData = Split(line, ' ');
			for (size_t i = 0; i < 3; i++)
			{
				std::vector<std::string> strIndices = Split(splittedData[i + 1], '/');
				//Vertex
				indices.push_back(stoul(strIndices[0])-1);
				//Texture coordinates
				//indices.push_back(stoul(strIndices[1])-1);
				//Normal vector
				//indices.push_back(stoul(strIndices[2])-1);
			}
		}
	}

	//for (size_t i = 0; i < sizeof(rawData) / sizeof(float); i+=5)
	//{
	//	verticesVec.push_back(glm::vec3(rawData[i], rawData[i+1], rawData[i+2]));
	//	texturesPos.push_back(glm::vec2(rawData[i+3], rawData[i+4]));
	//}

	Mesh testMesh(verticesVec, indices, normals, texturesPos);

	ResourceManager::GetInstance()->AddResource(new Image, "container", "C:\\Users\\willi\\Downloads\\container.jpg");
	Image* test = ResourceManager::GetInstance()->GetResource<Image>("container");
	test->LoadResource();
	Texture tex(*test);

	ResourceManager::GetInstance()->AddResource(new Image(true), "smiley", "C:\\Users\\willi\\Downloads\\awesomeface.png");
	Image* test2 = ResourceManager::GetInstance()->GetResource<Image>("smiley");
	test2->LoadResource();
	Texture tex2(*test2);

	//Uniform stuff
	window.GetRenderer().GetShaderProgram().SetInt("tex", 0);
	window.GetRenderer().GetShaderProgram().SetInt("tex2", 1);
	glfwSetInputMode(window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Render loop
	while (!window.ShouldClose())
	{
		tex.Bind(0);
		tex2.Bind(1);

		//Model matrix
		glm::mat4 model = glm::mat4(1.0f);

		//Uniform stuff
		window.GetRenderer().GetShaderProgram().Bind();
		window.GetRenderer().GetShaderProgram().SetMat4("model", model);

		window.GetRenderer().AddToRender(testMesh);
		window.Render();
	}
}