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

std::vector<Vertex> MeshFactory::CreateOval(float x, float y, float radius, float numberOfSegments)
{
	float angle{glm::radians( 360 / numberOfSegments )};

	glm::vec2 middle{ x,y };

	std::vector<Vertex> returnVec{};

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

std::vector<Vertex> MeshFactory::CreateRoundedQuad(float top, float bottom, float left,
	float right, float radius, float numberOfSegments)
{
	std::vector<Vertex> returnVec{};

	glm::vec2 middle{ left + (right - left) / 2,bottom + (top - bottom) / 2 };
	float angle{ glm::radians(90 / (numberOfSegments/4)) };

	//top right corner
	for (int i = 1; i <= numberOfSegments/4; i++)
	{
		Vertex v1{ { radius * glm::sin(angle * i),radius * glm::cos(angle * i) }, { 1.0f, 0.0f, 0.0f } };
		Vertex v2{ middle,{1.0f, 1.0f, 0.0f} };
		Vertex v3{ { radius * glm::sin(angle * (i + 1)),radius * glm::cos(angle * (i + 1)) }, { 1.0f, 0.0f, 0.0f } };
		returnVec.emplace_back(v1);
		returnVec.emplace_back(v2);
		returnVec.emplace_back(v3);
	}

	return returnVec;
}
