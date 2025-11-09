#pragma once
#include "MeshBB.h"

#include <string>
#include <array>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using std::array;
using std::string;
using std::vector;
using namespace glm;

class MeshCurveBB : public MeshBB
{
public:
	MeshCurveBB(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);

	void triangulate(
		vector<fvec3> *vertices,
		vector<fvec4> *colors);

	void render(float currentTime, float rotationAngleDegrees = 0.0f) override;

private:
	vector<unsigned int> indices;
};
