#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

using glm::fmat4;
using glm::fvec2;
using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class Mesh;
class MeshBB;

class MeshBuilder
{
public:
	// No numberOfTriangles parameter because it is always 2 for a plane
	static Mesh *buildPlane(string vertexShaderName,
							string fragmentShaderName,
							bool shouldPrintLogs,
							ivec2 windowSize,
							fvec3 position,
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
							  fvec3 position,
							  fvec3 scaleVector,
							  fvec4 colorCenter,
							  fvec4 colorBorder,
							  fmat4 modelMatrix);

private:
	MeshBuilder() = default;
	~MeshBuilder() = default;
};