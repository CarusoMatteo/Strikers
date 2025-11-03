#pragma once

#include <string>
#include <array>
#include <vector>
#include <glm/glm.hpp>

using glm::fmat4;
using glm::fvec2;
using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::array;
using std::string;
using std::vector;

class Mesh;
class MeshBB;

class MeshBuilder
{
public:
	static Mesh *buildBackgroundMesh(
		string vertexShaderName,
		string fragmentShaderName,
		bool shouldPrintLogs,
		// int numberOfTriangles, always 2
		ivec2 windowSize,
		fvec3 position,
		fvec3 scaleVector,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight,
		fmat4 modelMatrix);

	static MeshBB *buildHeartBB(
		string vertexShaderName,
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

	static MeshBB *buildRectangleBB(
		string vertexShaderName,
		string fragmentShaderName,
		bool shouldPrintLogs,
		// int numberOfTriangles, always 2
		float width,
		float height,
		ivec2 windowSize,
		fvec3 position,
		fvec3 scaleVector,
		fvec4 colorTopLeft,
		fvec4 colorTopRight,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fmat4 modelMatrix);

private:
	MeshBuilder() = default;
	~MeshBuilder() = default;

	static void initBoundingBox(vector<fvec3> &vertices, vector<fvec4> &colors);
};