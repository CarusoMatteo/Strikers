#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"

using glm::fvec3;
using glm::fvec4;
using std::vector;

class MeshBuilder
{
public:
	static Mesh *buildPlane(string vertexShaderName,
							string fragmentShaderName,
							bool shouldPrintLogs,
							int numberOfTriangles,
							ivec2 screenSize,
							fvec3 scaleVector,
							fvec4 colorTop,
							fvec4 colorBottom,
							mat4 modelMatrix);
	/*
	static Mesh *buildTriangle();
	static Mesh *buildTriangle();
	static Mesh *buildCircle();
	static Mesh *buildHeart();
	static Mesh *buildButterfly();
	static Mesh *buildSpaceship();
	*/

private:
	MeshBuilder() = default;
	~MeshBuilder() = default;
};