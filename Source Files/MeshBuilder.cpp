#include "../Header Files/MeshBuilder.h"

Mesh *MeshBuilder::buildPlane(
	string vertexShaderName,
	string fragmentShaderName,
	bool shouldPrintLogs,
	int numberOfPoints,
	ivec2 screenSize,
	fvec3 scaleVector,
	fvec4 colorTop,
	fvec4 colorBottom)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;
	vertices.push_back(vec3(0.0, 0.0, 0.0));
	colors.push_back(colorTop);
	vertices.push_back(vec3(1.0, 0.0, 0.0));
	colors.push_back(colorBottom);
	vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(colorTop);
	vertices.push_back(vec3(0.0, 1.0, 0.0));
	colors.push_back(colorBottom);

	Mesh *mesh = new Mesh(
		vertexShaderName,
		fragmentShaderName,
		shouldPrintLogs,
		numberOfPoints,
		vertices,
		colors,
		GL_TRIANGLE_FAN,
		screenSize, scaleVector);
	return mesh;
}

/*

Mesh *MeshBuilder::buildTriangle()
{
	Mesh mesh = Mesh();
	return mesh;
}


Mesh *MeshBuilder::buildCircle()
{
	Mesh mesh = Mesh();
	return mesh;
}

Mesh *MeshBuilder::buildHeart()
{
	Mesh mesh = Mesh();
	return mesh;
}

Mesh *MeshBuilder::buildButterfly()
{
	Mesh mesh = Mesh();
	return mesh;
}

Mesh *MeshBuilder::buildSpaceship()
{
	Mesh mesh = Mesh();
	return mesh;
}

*/