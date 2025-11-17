#pragma once

#include <utility>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shape.h"

using glm::fvec2;
using glm::fvec3;
using glm::fvec4;
using std::pair;
using std::string;
using std::vector;

/**
 * @brief A utility class for creating various 2D shapes with vertex and color data.
 */
class ShapeMaker
{
public:
	/// @brief Creates a background plane rectangle with specified corner colors.
	static Shape makeBackgroundPlane(
		// int numberOfTriangles = 2 because it's fixed in rectangles.
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight);

	/// @brief Creates a heart shape with specified parameters.
	/// @param addBoundingBox Whether to add a bounding box vertices to the vertices and color vectors.
	static Shape makeHeart(
		int numberOfTriangles,
		fvec2 radius,
		fvec4 colorCenter,
		fvec4 colorBorder,
		bool addBoundingBox = true);

	/// @brief Creates a rectangle with specified dimensions and corner colors.
	/// @param addBoundingBox Whether to add a bounding box vertices to the vertices and color vectors.
	static Shape makeRectangle(
		// int numberOfTriangles = 2,
		float width,
		float height,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight,
		bool addBoundingBox = true);

	/// @brief Creates a triangle with specified side length and vertex colors.
	/// @param addBoundingBox Whether to add a bounding box vertices to the vertices and color vectors.
	static Shape makeTriangle(
		float sideLength,
		fvec4 colorTop,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		bool addBoundingBox = true);

	/// @brief Creates a circle with specified parameters.
	/// @param addBoundingBox Whether to add a bounding box vertices to the vertices and color
	static Shape makeCircle(
		int numberOfTriangles,
		fvec2 radius,
		fvec4 colorCenter,
		fvec4 colorBorder,
		bool addBoundingBox = false);

	/// @brief Creates a Hermit curve shape from a file with specified parameters.
	/// @param addBoundingBox Whether to add a bounding box vertices to the vertices and color vectors.
	static Shape makeHermitCurve(
		string fileName,
		int numberOfTriangles,
		fvec4 colorTop,
		fvec4 colorBottom,
		bool addBoundingBox);

private:
	ShapeMaker() = default;
	~ShapeMaker() = default;

	/// @brief Calculates and adds bounding box vertices to the provided vertices and colors vectors.
	/// @param vertices The vector of vertices to which bounding box vertices will be added.
	/// @param colors The vector of colors to which bounding box colors (all white) will be added.
	static void addBoundingBoxVertices(vector<fvec3> *vertices, vector<fvec4> *colors);
};