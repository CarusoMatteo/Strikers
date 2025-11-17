#pragma once
#include "Mesh.h"

using std::string;
using std::vector;
using namespace glm;

/**
 * @brief Class representing a mesh with a bounding box for collision detection.
 */
class MeshBB : public Mesh
{
public:
	MeshBB() = default;
	MeshBB(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		float rotationDegrees,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);

	static bool *shouldDrawBoundingBoxRef()
	{
		return &MeshBB::drawBoundingBox;
	}
	static bool shouldDrawBoundingBox()
	{
		return MeshBB::drawBoundingBox;
	}
	/// @brief Checks for collision between two MeshBB objects using AABB method.
	static bool checkCollision(MeshBB *meshA, MeshBB *meshB);

	/**
	 * @brief Gets the size of the bounding box in world coordinates. This provides a good approximation of the mesh size in world space.
	 * @return fvec3 representing the size of the bounding box in world coordinates.
	 */
	fvec3 getSizeWorld()
	{
		return fvec3(
			this->getBoundingBoxMinWorld().x - this->getBoundingBoxMaxWorld().x,
			this->getBoundingBoxMaxWorld().y - this->getBoundingBoxMinWorld().y,
			this->getBoundingBoxMaxWorld().z - this->getBoundingBoxMinWorld().z);
	}

	/// @brief Gets the center of the bounding box in world coordinates.
	fvec3 getBBCenter();
	/// @brief Gets the rightmost point of the bounding box in world coordinates.
	fvec3 getBBRight();
	void render(float currentTime) override;

private:
	static bool drawBoundingBox;

	fvec4 getBoundingBoxMinObject();
	fvec4 getBoundingBoxMaxObject();
	fvec4 getBoundingBoxMinWorld();
	fvec4 getBoundingBoxMaxWorld();
};
