#include "../Header Files/MeshBB.h"
#include "../Header Files/ShaderBuilder.h"
#include "../Header Files/Renderer.h"

bool MeshBB::drawBoundingBox = false;

MeshBB::MeshBB(string vertexShaderName,
			   string fragmentShaderName,
			   vector<fvec3> vertices,
			   vector<fvec4> colors,
			   fvec3 position,
			   fvec3 scaleVector,
			   GLenum drawMode,
			   ivec2 windowSize,
			   fmat4 modelMatrix) : Mesh(vertexShaderName,
										 fragmentShaderName,
										 vertices,
										 colors,
										 position,
										 scaleVector,
										 drawMode,
										 windowSize,
										 modelMatrix)
{
	this->updateBoundingBoxWorld();
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

fvec4 MeshBB::getBoundingBoxMinObject()
{
	return fvec4(this->vertices[this->vertices.size() - 2], 1.0f);
}

fvec4 MeshBB::getBoundingBoxMaxObject()
{
	return fvec4(this->vertices[this->vertices.size() - 1], 1.0f);
}

void MeshBB::updateBoundingBoxWorld()
{
	this->boundingBoxMinWorld = this->modelMatrix * this->getBoundingBoxMinObject();
	this->boundingBoxMaxWorld = this->modelMatrix * this->getBoundingBoxMaxObject();
}