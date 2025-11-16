#pragma once
#include "Mesh.h"

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

// Warning: unused and incomplete
class MeshCurve : public Mesh
{
public:
	MeshCurve(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		float rotationDegrees,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);

	void triangulate(
		vector<fvec3> *vertices,
		vector<fvec4> *colors);

private:
	vector<unsigned int> indices;
};
