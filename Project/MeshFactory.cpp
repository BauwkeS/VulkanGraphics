#include "MeshFactory.h"

std::vector<Vertex> MeshFactory::CreateQuad(float top, float bottom, float left, float right)
{
	std::vector<Vertex> returnVec = {
		{{top,left},{1.0f, 0.0f, 0.0f}},
		{{bottom,right},{1.0f, 0.0f, 0.0f}},
		{{bottom,left},{1.0f, 0.0f, 0.0f}},

		{{top,right},{1.0f, 0.0f, 0.0f}},
		{{bottom,right},{1.0f, 0.0f, 0.0f}},
		{{top,left},{1.0f, 0.0f, 0.0f}},
	};
	
	return returnVec;
}

std::vector<Vertex> MeshFactory::createOval(float x, float y, float radius, float numberOfSegments)
{
	/*radius* glm::cos(angle), radius* glm::sin(angle) :D

	glm::radians(angle)*/

	float angle{glm::radians( 360 / numberOfSegments )};

	glm::vec2 middle{ x,y };

	std::vector<Vertex> returnVec = {
		/*{{radius * glm::sin(angle),radius * glm::cos(angle)},{1.0f, 0.0f, 0.0f}},
		{middle,{1.0f, 1.0f, 0.0f}},
		{{radius * glm::sin(angle*2),radius * glm::cos(angle*2)},{1.0f, 0.0f, 0.0f}},

		{{radius * glm::sin(angle * 2),radius * glm::cos(angle * 2)},{1.0f, 0.0f, 0.0f}},
		{middle,{1.0f, 1.0f, 0.0f}},
		{{radius * glm::sin(angle*3),radius * glm::cos(angle*3)},{1.0f, 0.0f, 0.0f}},*/
	};

	for (int i = 1; i <= numberOfSegments; i++)
	{
		Vertex v1{ { radius * glm::sin(angle*i),radius * glm::cos(angle*i) }, { 1.0f, 0.0f, 0.0f } };
		Vertex v2{ middle,{1.0f, 1.0f, 0.0f} };
		Vertex v3{ { radius * glm::sin(angle*(i+1)),radius * glm::cos(angle*(i+1)) }, { 1.0f, 0.0f, 0.0f } };
		returnVec.emplace_back(v1);
		returnVec.emplace_back(v2);
		returnVec.emplace_back(v3);
	}


	return returnVec;
}
