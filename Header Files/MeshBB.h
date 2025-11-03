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
		bool shouldPrintLogs,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		GLenum drawMode,
		ivec2 screenSize,
		fvec3 position,
		fvec3 scaleVector,
		fmat4 modelMatrix);

	static bool *shouldDrawBoundingBoxRef()
	{
		return &MeshBB::drawBoundingBox;
	}
	static bool shouldDrawBoundingBox()
	{
		return MeshBB::drawBoundingBox;
	}

	void render(float currentTime, float rotationAngleDegrees = 0.0f);

private:
	static bool drawBoundingBox;

	fvec4 boundingBoxMinObject;
	fvec4 boundingBoxMaxObject;
	fvec4 boundingBoxMinWorld;
	fvec4 boundingBoxMaxWorld;

	void initBoundingBox();
	void updateBoundingBoxWorld();
};
