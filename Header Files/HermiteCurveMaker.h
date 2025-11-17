#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "Shape.h"
#include "../Header Files/ParametrizationType.h"

using glm::distance;
using glm::fvec3;
using glm::fvec4;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using std::vector;

class Curve;

/**
 * Static class to read and create Hermite curves from files.
 */
class HermiteCurveMaker
{
public:
	/**
	 * @brief Returns a vector of Shapes representing Hermite curves read from a file.
	 * @param fileName The name of the file containing the Hermite curve definition.
	 * @param numberOfTriangles The number of triangles to use to triangulate the curve.
	 * @param colorTop The color at the border of the curve.
	 * @param colorBottom The color at the center of the curve.
	 * @return
	 */
	static vector<Shape> makeHermiteCurve(
		string fileName,
		int numberOfTriangles,
		fvec4 colorTop,
		fvec4 colorBottom);

private:
	HermiteCurveMaker() = default;
	~HermiteCurveMaker() = default;

	static ParameterizationType parameterization;

	static vector<Curve> readCurveSource(string fileName);
	static Shape buildCurve(
		Curve *curve,
		fvec4 colorTop,
		fvec4 colorBottom,
		int numberOfTriangles);

	static float PHI0(float t);
	static float PHI1(float t);
	static float PSI0(float t);
	static float PSI1(float t);

	static float dx(int i, vector<float> *t, Curve *curve);
	static float dy(int i, vector<float> *t, Curve *curve);
	static float dz(int i, vector<float> *t, Curve *curve);

	static vector<float> equidistant(Curve *curve);
	static vector<float> chord(Curve *curve);
};