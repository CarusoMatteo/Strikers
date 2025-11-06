#pragma once
#include "Mesh.h"

using std::string;
using std::vector;
using namespace glm;

class MeshBB : public Mesh
{
public:
	MeshBB(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);

	static bool *shouldDrawBoundingBoxRef()
	{
		return &MeshBB::drawBoundingBox;
	}
	static bool shouldDrawBoundingBox()
	{
		return MeshBB::drawBoundingBox;
	}
	static bool checkCollision(MeshBB *meshA, MeshBB *meshB);

	fvec3 getBBCenter();
	fvec3 getBBRight();
	void render(float currentTime, float rotationAngleDegrees = 0.0f);

private:
	static bool drawBoundingBox;

	fvec4 getBoundingBoxMinObject();
	fvec4 getBoundingBoxMaxObject();
	fvec4 getBoundingBoxMinWorld();
	fvec4 getBoundingBoxMaxWorld();
};
