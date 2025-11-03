#include "../Header Files/MeshBB.h"
bool MeshBB::drawBoundingBox = false;

MeshBB::MeshBB(string vertexShaderName,
			   string fragmentShaderName,
			   bool shouldPrintLogs,
			   vector<fvec3> vertices,
			   vector<fvec4> colors,
			   GLenum drawMode,
			   ivec2 windowSize,
			   fvec3 position,
			   fvec3 scaleVector,
			   fmat4 modelMatrix) : Mesh::Mesh(vertexShaderName,
											   fragmentShaderName,
											   shouldPrintLogs,
											   vertices,
											   colors,
											   drawMode,
											   windowSize,
											   position,
											   scaleVector,
											   modelMatrix)
{
	this->initBoundingBox();
}

void MeshBB::render(float currentTime, float rotationAngleDegrees)
{
	Renderer::renderWithBB(
		this->programId,
		&this->projectionMatrixUniformLocation, &MeshBB::projectionMatrix,
		&this->modelMatrixUniformLocation, &this->modelMatrix,
		&this->screenSizeUniformLocation, this->windowSize,
		&this->currentTimeUniformLocation, currentTime,
		&this->position, &this->scaleVector, rotationAngleDegrees,
		this->vaoAddress, this->drawMode, static_cast<int>(this->vertices.size()));
}

void MeshBB::initBoundingBox()
{
	int n = static_cast<int>(this->vertices.size());
	float minx = this->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
	float miny = this->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

	float maxx = this->vertices[0].x; // Assumiamo che il primo elemento sia il massimo iniziale
	float maxy = this->vertices[0].y; // Assumiamo che il primo elemento sia il massimo iniziale

	for (int i = 1; i < n; i++)
	{
		if (this->vertices[i].x < minx)
		{
			minx = this->vertices[i].x;
		}
		if (this->vertices[i].x > maxx)
		{
			maxx = this->vertices[i].x;
		}

		if (this->vertices[i].y < miny)
		{
			miny = this->vertices[i].y;
		}

		if (this->vertices[i].y > maxy)
		{
			maxy = this->vertices[i].y;
		}
	}

	this->boundingBoxMinObject = fvec4(minx, miny, 0.0, 1.0);
	this->boundingBoxMaxObject = fvec4(maxx, maxy, 0.0, 1.0);

	// Add bounding box vertices to the vertices vector
	this->vertices.push_back(fvec3(this->boundingBoxMinObject.x, this->boundingBoxMinObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	this->vertices.push_back(fvec3(this->boundingBoxMaxObject.x, this->boundingBoxMinObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	this->vertices.push_back(fvec3(this->boundingBoxMaxObject.x, this->boundingBoxMaxObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	this->vertices.push_back(fvec3(this->boundingBoxMinObject.x, this->boundingBoxMaxObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
}

void MeshBB::updateBoundingBoxWorld()
{
	this->boundingBoxMinWorld = this->modelMatrix * this->boundingBoxMinObject;
	this->boundingBoxMaxWorld = this->modelMatrix * this->boundingBoxMaxObject;
}