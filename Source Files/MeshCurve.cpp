#include "../Header Files/MeshCurve.h"
#include "../Header Files/Renderer.h"
#include "../Header Files/earcut.hpp"

// Warning: unused and incomplete

using Point2D = array<float, 2>;

MeshCurve::MeshCurve(
	string vertexShaderName,
	string fragmentShaderName,
	vector<fvec3> vertices,
	vector<fvec4> colors,
	fvec3 position,
	float rotationDegrees,
	fvec3 scaleVector,
	GLenum drawMode,
	ivec2 windowSize)
{
	this->triangulate(&vertices, &colors);
	Mesh(
		vertexShaderName,
		fragmentShaderName,
		vertices,
		colors,
		position,
		rotationDegrees,
		scaleVector,
		drawMode,
		windowSize);
}

void MeshCurve::triangulate(
	vector<fvec3> *vertices,
	vector<fvec4> *colors)
{
	vector<Point2D> polygon2D;
	polygon2D.reserve(vertices->size());
	for (auto &&vertex : *vertices)
		polygon2D.push_back(Point2D{vertex.x, vertex.y});

	vector<vector<Point2D>> polygon = {polygon2D};
	// Triangolazione facebndo uso della funzione eartcut
	vector<unsigned int> indices = mapbox::earcut<unsigned int>(polygon);
	// Output degli indici dei triangoli
	this->indices = indices;
}
