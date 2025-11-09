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

class ShapeMaker
{
public:
	static Shape makeBackgroundPlane(
		// int numberOfTriangles = 2,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight);

	static Shape makeHeart(
		int numberOfTriangles,
		fvec2 radius,
		fvec4 colorCenter,
		fvec4 colorBorder,
		bool addBoundingBox = true);

	static Shape makeRectangle(
		// int numberOfTriangles = 2,
		float width,
		float height,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight,
		bool addBoundingBox = true);

	static Shape makeTriangle(
		float sideLength,
		fvec4 colorTop,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		bool addBoundingBox = true);

	static Shape makeCircle(
		int numberOfTriangles,
		fvec2 radius,
		fvec4 colorCenter,
		fvec4 colorBorder,
		bool addBoundingBox = false);

	static Shape makeHermitCurve(
		string fileName,
		int numberOfTriangles,
		fvec4 colorTop,
		fvec4 colorBottom,
		bool addBoundingBox);

private:
	ShapeMaker() = default;
	~ShapeMaker() = default;

	static void addBoundingBoxVertices(vector<fvec3> *vertices, vector<fvec4> *colors);
};