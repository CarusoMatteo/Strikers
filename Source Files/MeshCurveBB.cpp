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
	float rotationDegrees,
	fvec3 scaleVector,
	GLenum drawMode,
	ivec2 windowSize)
{
	this->vertices = vertices;
	this->colors = colors;
	this->position = position;
	this->rotationDegrees = rotationDegrees;
	this->scaleVector = scaleVector;
	this->drawMode = drawMode;
	this->windowSize = windowSize;

	this->modelMatrix = fmat4(1);
	this->creationTime = static_cast<float>(glfwGetTime());
	this->triangulate(&vertices, &colors);
	this->buildShader(vertexShaderName, fragmentShaderName);
	this->initVao();
	this->initVbos();
	this->initUniformReferences();
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

	vector<vector<Point2D>> polygon = {polygon2D};
	// Triangulation using the earcut function
	vector<unsigned int> indices = mapbox::earcut<unsigned int>(polygon);
	// Triangle indices
	this->indices = indices;
}

void MeshCurveBB::render(float currentTime)
{
	int vertexCount = static_cast<int>(this->vertices.size());
	Renderer::renderCurveWithBB(
		this->programId,
		&this->projectionMatrixUniformLocation, &Mesh::projectionMatrix,
		&this->modelMatrixUniformLocation, &this->modelMatrix,
		&this->screenSizeUniformLocation, fvec2(this->windowSize),
		&this->creationTimeUniformLocation, this->creationTime,
		&this->currentTimeUniformLocation, currentTime,
		&this->isVisibleUniformLocation, this->isVisible,
		&this->position, &this->scaleVector, this->rotationDegrees,
		this->vaoAddress,
		this->drawMode,
		static_cast<int>(this->indices.size()),
		&vertexCount);
}

void MeshCurveBB::initVbos()
{
	// Generates and makes active the VBO for the vertices
	glGenBuffers(1, &this->verticesVboAddress);
	glBindBuffer(GL_ARRAY_BUFFER, this->verticesVboAddress);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(fvec3), this->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	// Generates and makes active the VBO for the colors
	glGenBuffers(1, &this->colorsVboAddress);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorsVboAddress);
	glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(fvec4), this->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);

	// Generates and makes active the EBO for the indices
	glGenBuffers(1, &this->indicesEboAddress);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesEboAddress);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);
}
