#pragma once
#include "Mesh.h"

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using std::string;
using std::vector;
using namespace glm;

class MeshCurve : public Mesh
{
public:
	MeshCurve(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);

	void render(float currentTime, float rotationAngleDegrees = 0.0f) override;
};
