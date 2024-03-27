#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>

class Scene
{
public:


private:
	Pipeline m_pipeline;
	std::vector<MeshFactory*> m_MeshFactoryVector;
	Command* m_commandInfo;
	Shader* m_gradientShaderInfo;
};

//Create a class that can contain multiple of theses meshes.
// For now, there is just one graphics pipeline and one shader and all meshes
// use the same shader, but that will change in the future.
// How will you create  the link between a mesh, a shader and a graphics pipeline.