#include "../Header Files/MeshCurveBB.h"
#include "../Header Files/Renderer.h"
#include "../Header Files/earcut.hpp"

using Point2D = array<float, 2>;

MeshCurveBB::MeshCurveBB(
	string vertexShaderName,
	string fragmentShaderName,
	vector<fvec3> vertices,
	vector<fvec4> colors,
	fvec3 position,
	fvec3 scaleVector,
	GLenum drawMode,
	ivec2 windowSize)
{
	this->triangulate(&vertices, &colors);
	MeshBB(
		vertexShaderName,
		fragmentShaderName,
		vertices,
		colors,
		position,
		scaleVector,
		drawMode,
		windowSize);
}

void MeshCurveBB::triangulate(
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
