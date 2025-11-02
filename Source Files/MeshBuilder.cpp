#include "../Header Files/MeshBuilder.h"

MeshBB *MeshBuilder::buildPlane(
	string vertexShaderName,
	string fragmentShaderName,
	bool shouldPrintLogs,
	ivec2 screenSize,
	fvec3 scaleVector,
	fvec4 colorBottomLeft,
	fvec4 colorBottomRight,
	fvec4 colorTopLeft,
	fvec4 colorTopRight,
	mat4 modelMatrix)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;
	vertices.push_back(vec3(0.0, 0.0, 0.0));
	colors.push_back(colorBottomLeft);
	vertices.push_back(vec3(1.0, 0.0, 0.0));
	colors.push_back(colorBottomRight);
	vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(colorTopRight);
	vertices.push_back(vec3(0.0, 1.0, 0.0));
	colors.push_back(colorTopLeft);

	MeshBB *mesh = new MeshBB(
		vertexShaderName,
		fragmentShaderName,
		shouldPrintLogs,
		vertices,
		colors,
		GL_TRIANGLE_FAN,
		screenSize,
		scaleVector,
		modelMatrix);
	return mesh;
}
