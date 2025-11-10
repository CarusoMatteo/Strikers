#include "../Header Files/MeshBB.h"
#include "../Header Files/ShaderBuilder.h"
#include "../Header Files/Renderer.h"

bool MeshBB::drawBoundingBox = false;

MeshBB::MeshBB(
	string vertexShaderName,
	string fragmentShaderName,
	vector<fvec3> vertices,
	vector<fvec4> colors,
	fvec3 position,
	float rotationDegrees,
	fvec3 scaleVector,
	GLenum drawMode,
	ivec2 windowSize) : Mesh(vertexShaderName,
							 fragmentShaderName,
							 vertices,
							 colors,
							 position,
							 rotationDegrees,
							 scaleVector,
							 drawMode,
							 windowSize)
{
}

fvec3 MeshBB::getBBCenter()
{
	fvec4 boundingBoxMinWorld = this->getBoundingBoxMinWorld();
	fvec4 boundingBoxMaxWorld = this->getBoundingBoxMaxWorld();

	return fvec3(
		(boundingBoxMinWorld.x + boundingBoxMaxWorld.x) / 2.0f,
		(boundingBoxMinWorld.y + boundingBoxMaxWorld.y) / 2.0f,
		(boundingBoxMinWorld.z + boundingBoxMaxWorld.z) / 2.0f);
}

fvec3 MeshBB::getBBRight()
{
	fvec4 boundingBoxMinWorld = this->getBoundingBoxMinWorld();
	fvec4 boundingBoxMaxWorld = this->getBoundingBoxMaxWorld();

	return fvec3(
		boundingBoxMaxWorld.x,
		(boundingBoxMinWorld.y + boundingBoxMaxWorld.y) / 2.0f,
		(boundingBoxMinWorld.z + boundingBoxMaxWorld.z) / 2.0f);
}

bool MeshBB::checkCollision(MeshBB *meshA, MeshBB *meshB)
{
	fvec4 bbAMin = meshA->getBoundingBoxMinWorld();
	fvec4 bbAMax = meshA->getBoundingBoxMaxWorld();
	fvec4 bbBMin = meshB->getBoundingBoxMinWorld();
	fvec4 bbBMax = meshB->getBoundingBoxMaxWorld();

	bool collisionX = (bbAMin.x <= bbBMax.x) && (bbAMax.x > bbBMin.x);
	bool collisionY = (bbAMin.y <= bbBMax.y) && (bbAMax.y > bbBMin.y);
	return collisionX && collisionY;
}

void MeshBB::render(float currentTime)
{
	Renderer::renderWithBB(
		this->programId,
		&this->projectionMatrixUniformLocation, &MeshBB::projectionMatrix,
		&this->modelMatrixUniformLocation, &this->modelMatrix,
		&this->screenSizeUniformLocation, this->windowSize,
		&this->creationTimeUniformLocation, creationTime,
		&this->currentTimeUniformLocation, currentTime,
		&this->isVisibleUniformLocation, this->isVisible,
		&this->position, &this->scaleVector, this->rotationDegrees,
		this->vaoAddress, this->drawMode, static_cast<int>(this->vertices.size()));
}

fvec4 MeshBB::getBoundingBoxMinObject()
{
	return fvec4(this->vertices.at(this->vertices.size() - 4), 1.0f);
}

fvec4 MeshBB::getBoundingBoxMaxObject()
{
	return fvec4(this->vertices.at(this->vertices.size() - 2), 1.0f);
}

fvec4 MeshBB::getBoundingBoxMinWorld()
{
	/*
	 * 	fmat4 translated = translate(this->modelMatrix, this->position);
	 *	fmat4 rotated = rotate(translated, glm::radians(rotationDegrees), glm::fvec3(0, 0, 1));
	 *	fmat4 scaled = scale(rotated, this->scaleVector);
	 *	return scaled * this->getBoundingBoxMinObject();
	 */
	return this->modelMatrix * this->getBoundingBoxMinObject();
}

fvec4 MeshBB::getBoundingBoxMaxWorld()
{
	/*
	 * 	fmat4 translated = translate(this->modelMatrix, this->position);
	 *	fmat4 rotated = rotate(translated, glm::radians(rotationDegrees), glm::fvec3(0, 0, 1));
	 *	fmat4 scaled = scale(rotated, this->scaleVector);
	 *	return scaled * this->getBoundingBoxMaxObject();
	 */
	return this->modelMatrix * this->getBoundingBoxMaxObject();
}