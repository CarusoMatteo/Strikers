#include "../Header Files/MeshBuilder.h"

#include "../Header Files/MeshBB.h"

Mesh *MeshBuilder::buildPlane(
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

	return new Mesh(
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

MeshBB *MeshBuilder::buildRectangleBB(
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
	fmat4 modelMatrix)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;

	vertices.push_back(fvec3(0));
	colors.push_back(colorTopLeft);
	vertices.push_back(fvec3(width, 0, 0));
	colors.push_back(colorTopRight);
	vertices.push_back(fvec3(width, height, 0));
	colors.push_back(colorBottomRight);
	vertices.push_back(fvec3(0, height, 0));
	colors.push_back(colorBottomLeft);

	MeshBuilder::initBoundingBox(vertices, colors);

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

MeshBB *MeshBuilder::buildHeartBB(
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

	MeshBuilder::initBoundingBox(vertices, colors);

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

void MeshBuilder::initBoundingBox(vector<fvec3> &vertices, vector<fvec4> &colors)
{
	int n = static_cast<int>(vertices.size());
	float minx = vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
	float miny = vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

	float maxx = vertices[0].x; // Assumiamo che il primo elemento sia il massimo iniziale
	float maxy = vertices[0].y; // Assumiamo che il primo elemento sia il massimo iniziale

	for (int i = 1; i < n; i++)
	{
		if (vertices[i].x < minx)
		{
			minx = vertices[i].x;
		}
		if (vertices[i].x > maxx)
		{
			maxx = vertices[i].x;
		}

		if (vertices[i].y < miny)
		{
			miny = vertices[i].y;
		}

		if (vertices[i].y > maxy)
		{
			maxy = vertices[i].y;
		}
	}

	fvec4 boundingBoxMinObject = fvec4(minx, miny, 0.0, 1.0);
	fvec4 boundingBoxMaxObject = fvec4(maxx, maxy, 0.0, 1.0);

	// Add bounding box vertices to the vertices vector
	vertices.push_back(fvec3(boundingBoxMinObject.x, boundingBoxMinObject.y, 0.0));
	colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(fvec3(boundingBoxMaxObject.x, boundingBoxMinObject.y, 0.0));
	colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(fvec3(boundingBoxMaxObject.x, boundingBoxMaxObject.y, 0.0));
	colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(fvec3(boundingBoxMinObject.x, boundingBoxMaxObject.y, 0.0));
	colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
}
