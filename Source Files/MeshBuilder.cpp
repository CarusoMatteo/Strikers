#include "../Header Files/MeshBuilder.h"

MeshBB *MeshBuilder::buildPlane(
	string vertexShaderName,
	string fragmentShaderName,
	bool shouldPrintLogs,
	ivec2 windowSize,
	fvec3 position,
	fvec3 scaleVector,
	fvec4 colorBottomLeft,
	fvec4 colorBottomRight,
	fvec4 colorTopLeft,
	fvec4 colorTopRight,
	fmat4 modelMatrix)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;
	vertices.push_back(fvec3(0.0, 0.0, 0.0));
	colors.push_back(colorBottomLeft);
	vertices.push_back(fvec3(1.0, 0.0, 0.0));
	colors.push_back(colorBottomRight);
	vertices.push_back(fvec3(1.0, 1.0, 0.0));
	colors.push_back(colorTopRight);
	vertices.push_back(fvec3(0.0, 1.0, 0.0));
	colors.push_back(colorTopLeft);

	return new MeshBB(
		vertexShaderName,
		fragmentShaderName,
		shouldPrintLogs,
		vertices,
		colors,
		GL_TRIANGLE_FAN,
		windowSize,
		position,
		scaleVector,
		modelMatrix);
}

MeshBB *MeshBuilder::buildHeart(
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
	fmat4 modelMatrix)
{
	float pi = static_cast<float>(3.14159265358979323846);
	vector<fvec3> vertices;
	vector<fvec4> colors;

	vertices.push_back(fvec3(center.x, center.y, 0.0));
	colors.push_back(colorCenter);

	float step = (2 * pi) / numberOfTriangles;
	for (int i = 0; i <= numberOfTriangles; i++)
	{
		float t = i * step;
		float xx = center.x + radius.x * (16 * powf(sin(t), 3));
		float yy = center.y + radius.y * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)));
		vertices.push_back(fvec3(xx, yy, 0.0));
		colors.push_back(colorBorder);
	}

	return new MeshBB(
		vertexShaderName,
		fragmentShaderName,
		shouldPrintLogs,
		vertices,
		colors,
		GL_TRIANGLE_FAN,
		windowSize,
		position,
		scaleVector,
		modelMatrix);
}
