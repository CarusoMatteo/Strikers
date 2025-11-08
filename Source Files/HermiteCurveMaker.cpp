#include "../Header Files/HermiteCurveMaker.h"

#pragma region Classes

class ControlPoint
{
public:
	ControlPoint() = default;
	~ControlPoint() = default;
	fvec3 position;
	float tension;
	float bias;
	float continuity;
};

class Curve
{
public:
	Curve() = default;
	~Curve() = default;
	vector<ControlPoint> controlPoints;
	// If it's the 0 vector, it means they haven't been modified
	vector<fvec3> derivatives;
	vector<unsigned int> indices;
	vector<float> distNormalized;
};

#pragma endregion

ParameterizationType HermiteCurveMaker::parameterization = ParameterizationType::EQUIDISTANT;

vector<Shape> HermiteCurveMaker::makeHermiteCurve(
	string fileName,
	fvec4 colorTop,
	fvec4 colorBottom,
	int numberOfTriangles)
{
	vector<fvec3> points;
	vector<Curve> curves = readCurveSource(fileName);
	vector<Shape> shapes;
	for (auto &&curve : curves)
	{
		Shape shape = buildCurve(&curve, colorTop, colorBottom, numberOfTriangles);
		shapes.push_back(shape);
	}
	return shapes;
}

#pragma warning(disable : 6386)
#pragma warning(disable : 4996)
vector<Curve> HermiteCurveMaker::readCurveSource(string fileName)
{
	FILE *file = fopen(fileName.c_str(), "r");
	if (!file)
	{
		throw runtime_error("Could not open Hermite curve source file: " + fileName);
	}

	vector<Curve> curves;
	Curve curve;

	int previousCurveNumber = 0;
	int currentCurveNumber = 0;
	for (ControlPoint currentPoint;
		 fscanf(file, "%d %f %f %f %f %f %f",
				&currentCurveNumber,
				&currentPoint.position.x, &currentPoint.position.y, &currentPoint.position.z,
				&currentPoint.tension, &currentPoint.bias, &currentPoint.continuity) == 7;)
	{
		if (currentCurveNumber == previousCurveNumber)
		{
			// This is part of the current curve
			curve.controlPoints.push_back(currentPoint);
		}
		else
		{
			cout << "Finished reading curve " << currentCurveNumber << " with " << curve.controlPoints.size() << " control points." << endl;
			// This is a new curve
			curves.push_back(curve);
			curve.controlPoints.clear();
			previousCurveNumber = currentCurveNumber;
			curve.controlPoints.push_back(currentPoint);
		}
	}
	// Add the last curve
	cout << "Finished reading curve " << currentCurveNumber << " with " << curve.controlPoints.size() << " control points." << endl;
	curves.push_back(curve);
	fclose(file);
	return curves;
}

Shape HermiteCurveMaker::buildCurve(
	Curve *curve,
	fvec4 colorTop,
	fvec4 colorBottom,
	int numberOfTriangles)
{
	vector<float> t = HermiteCurveMaker::parameterization == ParameterizationType::EQUIDISTANT
						  ? equidistant(curve)
						  : chord(curve);
	vector<fvec3> vertices;
	vector<fvec4> colors;

	float step = 1.0f / numberOfTriangles - 1;

	// Index of the left endpoint of the interval [t(i),t(i+1)] to which the tangent point belongs
	int leftEndpointIndex = 0;

	for (float tangent = 0; tangent <= 1; tangent += step)
	{
		// Find the interval to which tangent belongs
		if (tangent > t[leftEndpointIndex + 1])
			leftEndpointIndex++;

		float ampiezza = (t[leftEndpointIndex + 1] - t[leftEndpointIndex]);

		// Map tg in the interval [0,1]
		float tgmapp = (tangent - t[leftEndpointIndex]) / ampiezza;

		float x = curve->controlPoints[leftEndpointIndex].position.x * PHI0(tgmapp) +
				  dx(leftEndpointIndex, &t, curve) * PHI1(tgmapp) * ampiezza +
				  curve->controlPoints[leftEndpointIndex + 1].position.x * PSI0(tgmapp) +
				  dx(leftEndpointIndex + 1, &t, curve) * PSI1(tgmapp) * ampiezza;
		float y = curve->controlPoints[leftEndpointIndex].position.y * PHI0(tgmapp) +
				  dy(leftEndpointIndex, &t, curve) * PHI1(tgmapp) * ampiezza +
				  curve->controlPoints[leftEndpointIndex + 1].position.y * PSI0(tgmapp) +
				  dy(leftEndpointIndex + 1, &t, curve) * PSI1(tgmapp) * ampiezza;
		float z = 0.0f;
		/*
		 * float z = curve.controlPoints[leftEndpointIndex].position.y * PHI0(tgmapp) +
		 * 			 dz(leftEndpointIndex, &t, &curve) * PHI1(tgmapp) * ampiezza +
		 * 		  	 curve.controlPoints[leftEndpointIndex + 1].position.z * PSI0(tgmapp) +
		 * 			 dz(leftEndpointIndex + 1, &t, &curve) * PSI1(tgmapp) * ampiezza;
		 */

		vertices.push_back(fvec3(x, y, z));
		colors.push_back(colorBottom);
	}
	return Shape(vertices, colors);
}

#pragma region Hermite helper functions

float HermiteCurveMaker::PHI0(float t) { return 2.0f * t * t * t - 3.0f * t * t + 1.0f; }
float HermiteCurveMaker::PHI1(float t) { return t * t * t - 2.0f * t * t + t; }
float HermiteCurveMaker::PSI0(float t) { return -2.0f * t * t * t + 3.0f * t * t; }
float HermiteCurveMaker::PSI1(float t) { return t * t * t - t * t; }

float HermiteCurveMaker::dx(int i, vector<float> *t, Curve *curve)
{
	if (curve->derivatives.at(i).x != 0)
		return curve->derivatives.at(i).x;

	if (i == 0)
		return 0.5f *
			   (1 - curve->controlPoints.at(i).tension) *
			   (1 - curve->controlPoints.at(i).bias) *
			   (1 - curve->controlPoints.at(i).continuity) *
			   (curve->controlPoints.at(i + 1).position.x - curve->controlPoints.at(i).position.x) / (t->at(i + 1) - t->at(i));
	if (i == curve->controlPoints.size() - 1)
		return 0.5f *
			   (1 - curve->controlPoints.at(i).tension) *
			   (1 - curve->controlPoints.at(i).bias) *
			   (1 - curve->controlPoints.at(i).continuity) *
			   (curve->controlPoints.at(i).position.x - curve->controlPoints.at(i - 1).position.x) / (t->at(i) - t->at(i - 1));
	if (i % 2 == 0)
		return 0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 + curve->controlPoints.at(i).bias) *
				   (1 + curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i).position.x - curve->controlPoints.at(i - 1).position.x) / (t->at(i) - t->at(i - 1)) +
			   0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 - curve->controlPoints.at(i).bias) *
				   (1 - curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i + 1).position.x - curve->controlPoints.at(i).position.x) / (t->at(i + 1) - t->at(i));
	else
		return 0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 + curve->controlPoints.at(i).bias) *
				   (1 - curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i).position.x - curve->controlPoints.at(i - 1).position.x) / (t->at(i) - t->at(i - 1)) +
			   0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 - curve->controlPoints.at(i).bias) *
				   (1 + curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i + 1).position.x - curve->controlPoints.at(i).position.x) / (t->at(i + 1) - t->at(i));
}

float HermiteCurveMaker::dy(int i, vector<float> *t, Curve *curve)
{
	if (curve->derivatives.at(i).y != 0)
		return curve->derivatives.at(i).y;

	if (i == 0)
		return 0.5f *
			   (1 - curve->controlPoints.at(i).tension) *
			   (1 - curve->controlPoints.at(i).bias) *
			   (1 - curve->controlPoints.at(i).continuity) *
			   (curve->controlPoints.at(i + 1).position.y - curve->controlPoints.at(i).position.y) / (t->at(i + 1) - t->at(i));
	if (i == curve->controlPoints.size() - 1)
		return 0.5f *
			   (1 - curve->controlPoints.at(i).tension) *
			   (1 - curve->controlPoints.at(i).bias) *
			   (1 - curve->controlPoints.at(i).continuity) *
			   (curve->controlPoints.at(i).position.y - curve->controlPoints.at(i - 1).position.y) / (t->at(i) - t->at(i - 1));
	if (i % 2 == 0)
		return 0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 + curve->controlPoints.at(i).bias) *
				   (1 + curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i).position.y - curve->controlPoints.at(i - 1).position.y) / (t->at(i) - t->at(i - 1)) +
			   0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 - curve->controlPoints.at(i).bias) *
				   (1 - curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i + 1).position.y - curve->controlPoints.at(i).position.y) / (t->at(i + 1) - t->at(i));
	else
		return 0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 + curve->controlPoints.at(i).bias) *
				   (1 - curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i).position.y - curve->controlPoints.at(i - 1).position.y) / (t->at(i) - t->at(i - 1)) +
			   0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 - curve->controlPoints.at(i).bias) *
				   (1 + curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i + 1).position.y - curve->controlPoints.at(i).position.y) / (t->at(i + 1) - t->at(i));
}

float HermiteCurveMaker::dz(int i, vector<float> *t, Curve *curve)
{
	if (curve->derivatives.at(i).y != 0)
		return curve->derivatives.at(i).y;

	if (i == 0)
		return 0.5f *
			   (1 - curve->controlPoints.at(i).tension) *
			   (1 - curve->controlPoints.at(i).bias) *
			   (1 - curve->controlPoints.at(i).continuity) *
			   (curve->controlPoints.at(i + 1).position.z - curve->controlPoints.at(i).position.z) / (t->at(i + 1) - t->at(i));
	if (i == curve->controlPoints.size() - 1)
		return 0.5f *
			   (1 - curve->controlPoints.at(i).tension) *
			   (1 - curve->controlPoints.at(i).bias) *
			   (1 - curve->controlPoints.at(i).continuity) *
			   (curve->controlPoints.at(i).position.z - curve->controlPoints.at(i - 1).position.z) / (t->at(i) - t->at(i - 1));
	if (i % 2 == 0)
		return 0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 + curve->controlPoints.at(i).bias) *
				   (1 + curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i).position.z - curve->controlPoints.at(i - 1).position.z) / (t->at(i) - t->at(i - 1)) +
			   0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 - curve->controlPoints.at(i).bias) *
				   (1 - curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i + 1).position.z - curve->controlPoints.at(i).position.z) / (t->at(i + 1) - t->at(i));
	else
		return 0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 + curve->controlPoints.at(i).bias) *
				   (1 - curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i).position.z - curve->controlPoints.at(i - 1).position.z) / (t->at(i) - t->at(i - 1)) +
			   0.5f *
				   (1 - curve->controlPoints.at(i).tension) *
				   (1 - curve->controlPoints.at(i).bias) *
				   (1 + curve->controlPoints.at(i).continuity) *
				   (curve->controlPoints.at(i + 1).position.z - curve->controlPoints.at(i).position.z) / (t->at(i + 1) - t->at(i));
}

vector<float> HermiteCurveMaker::equidistant(Curve *curve)
{
	size_t size = curve->controlPoints.size();
	vector<float> t = vector<float>(size);

	float step = 1.0f / (size - 1);
	for (int i = 0; i < size; i++)
	{
		t.at(i) = step * i;
	}
	t.at(size - 1) = 1.0f;
	return t;
}

vector<float> HermiteCurveMaker::chord(Curve *curve)
{
	size_t size = curve->controlPoints.size();
	vector<float> t = vector<float>(size);

	t.at(0) = 0;
	for (int i = 1; i < size; i++)
	{
		t.at(i) = t.at(i - 1) + distance(curve->controlPoints.at(i - 1).position, curve->controlPoints.at(i).position);
	}

	for (int i = 0; i < size; i++)
	{
		t.at(i) = t.at(i) / t.at(size - 1);
	}
	return t;
}

#pragma endregion
