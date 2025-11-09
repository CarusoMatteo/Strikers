#include "../Header Files/MeshCurveBB.h"
#include "../Header Files/Renderer.h"
#include "../Header Files/earcut.hpp"
#include <iostream>

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

	// Remove the last four vertices if there are at least four because they are for the bounding box
	if (polygon2D.size() >= 4)
	{
		polygon2D.erase(polygon2D.end() - 4, polygon2D.end());
	}

	// Print the contents x, y of the polygon2D array
	for (const auto& pt : polygon2D) {
		std::cout << "x: " << pt[0] << ", y: " << pt[1] << std::endl;
	}

	vector<vector<Point2D>> polygon = {polygon2D};
	// Triangulation using the earcut function
	vector<unsigned int> indices = mapbox::earcut<unsigned int>(polygon);
	// Triangle indices
	this->indices = indices;
}

void MeshCurveBB::render(float currentTime, float rotationAngleDegrees)
{
	Renderer::renderCurveWithBB(
		this->programId,
		&this->projectionMatrixUniformLocation, &Mesh::projectionMatrix,
		&this->modelMatrixUniformLocation, &this->modelMatrix,
		&this->screenSizeUniformLocation, fvec2(this->windowSize),
		&this->creationTimeUniformLocation, this->creationTime,
		&this->currentTimeUniformLocation, currentTime,
		&this->isVisibleUniformLocation, this->isVisible,
		&this->position, &this->scaleVector, rotationAngleDegrees,
		this->vaoAddress,
		this->drawMode,
		static_cast<int>(this->indices.size()));
}