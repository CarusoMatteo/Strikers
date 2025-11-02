#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "MeshBB.h"

using glm::fvec3;
using glm::fvec4;
using std::vector;

class MeshBuilder
{
public:
	// No numberOfTriangles parameter because it is always 2 for a plane
	static MeshBB *buildPlane(string vertexShaderName,
							  string fragmentShaderName,
							  bool shouldPrintLogs,
							  ivec2 windowSize,
							  fvec3 scaleVector,
							  fvec4 colorBottomLeft,
							  fvec4 colorBottomRight,
							  fvec4 colorTopLeft,
							  fvec4 colorTopRight,
							  fmat4 modelMatrix);

	static MeshBB *buildHeart(string vertexShaderName,
							  string fragmentShaderName,
							  bool shouldPrintLogs,
							  int numberOfTriangles,
							  fvec2 center,
							  fvec2 radius,
							  ivec2 windowSize,
							  fvec3 scaleVector,
							  fvec4 colorCenter,
							  fvec4 colorBorder,
							  fmat4 modelMatrix);
	/*
	static Mesh *buildTriangle(string vertexShaderName,
							string fragmentShaderName,
							bool shouldPrintLogs,
							int numberOfTriangles,
							ivec2 windowSize,
							fvec3 scaleVector,
							fvec4 colorTop,
							fvec4 colorBottom,
							fmat4 modelMatrix);
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