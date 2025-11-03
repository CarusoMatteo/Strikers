#pragma once

#include <utility>
#include <vector>
#include <glm/glm.hpp>

using glm::fvec2;
using glm::fvec3;
using glm::fvec4;
using std::pair;
using std::vector;

class ShapeMaker
{
public:
	static pair<vector<fvec3>, vector<fvec4>> makeBackgroundPlane(
		// int numberOfTriangles = 2,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight);

	static pair<vector<fvec3>, vector<fvec4>> makeHeart(
		int numberOfTriangles,
		fvec2 radius,
		fvec4 colorCenter,
		fvec4 colorBorder);

	static pair<vector<fvec3>, vector<fvec4>> makeRectangle(
		// int numberOfTriangles = 2,
		float width,
		float height,
		fvec4 colorBottomLeft,
		fvec4 colorBottomRight,
		fvec4 colorTopLeft,
		fvec4 colorTopRight);

private:
	ShapeMaker() = default;
	~ShapeMaker() = default;

	static void addBoundingBoxVertices(vector<fvec3> *vertices, vector<fvec4> *colors);
};