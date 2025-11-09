#include "../Header Files/MeshCurve.h"
#include "../Header Files/Renderer.h"
#include "../Header Files/earcut.hpp"

using Point2D = array<float, 2>;

MeshCurve::MeshCurve(
	string vertexShaderName,
	string fragmentShaderName,
	vector<fvec3> vertices,
	vector<fvec4> colors,
	fvec3 position,
	fvec3 scaleVector,
	GLenum drawMode,
	ivec2 windowSize)
{
	this->modelMatrix = fmat4(1);
	this->creationTime = static_cast<float>(glfwGetTime());
	this->triangulate(&vertices, &colors);
	this->buildShader(vertexShaderName, fragmentShaderName);
	this->initVao();
	this->initVbos();
	this->initUniformReferences();
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

void MeshCurve::render(float currentTime, float rotationAngleDegrees)
{
	Renderer::renderWithoutBB(
		this->programId,
		&this->projectionMatrixUniformLocation, &Mesh::projectionMatrix,
		&this->modelMatrixUniformLocation, &this->modelMatrix,
		&this->screenSizeUniformLocation, this->windowSize,
		&this->creationTimeUniformLocation, creationTime,
		&this->currentTimeUniformLocation, currentTime,
		&this->isVisibleUniformLocation, this->isVisible,
		&this->position, &this->scaleVector, rotationAngleDegrees,
		this->vaoAddress, this->drawMode, static_cast<int>(this->vertices.size()));
}
