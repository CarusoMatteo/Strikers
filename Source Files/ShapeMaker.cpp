#include "../Header Files/ShapeMaker.h"

#include "../Header Files/HermiteCurveMaker.h"

float pi = 3.14159265358979323846f;

Shape ShapeMaker::makeBackgroundPlane(
	fvec4 colorBottomLeft,
	fvec4 colorBottomRight,
	fvec4 colorTopLeft,
	fvec4 colorTopRight)
{
	float width = 1;
	float height = 1;

	return ShapeMaker::makeRectangle(
		width,
		height,
		colorBottomLeft,
		colorBottomRight,
		colorTopLeft,
		colorTopRight,
		false);
}

Shape ShapeMaker::makeHeart(
	int numberOfTriangles,
	fvec2 radius,
	fvec4 colorCenter,
	fvec4 colorBorder,
	bool addBoundingBox)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;

	vertices.push_back(fvec3(0));
	colors.push_back(colorCenter);

	float step = 2 * pi / numberOfTriangles;
	for (int i = 0; i <= numberOfTriangles; i++)
	{
		float t = i * step;
		float xx = radius.x * (16 * powf(sin(t), 3));
		float yy = radius.y * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)));
		vertices.push_back(fvec3(xx, yy, 0));
		colors.push_back(colorBorder);
	}

	if (addBoundingBox)
	{
		ShapeMaker::addBoundingBoxVertices(&vertices, &colors);
	}

	return Shape(vertices, colors);
}

Shape ShapeMaker::makeRectangle(
	float width,
	float height,
	fvec4 colorBottomLeft,
	fvec4 colorBottomRight,
	fvec4 colorTopLeft,
	fvec4 colorTopRight,
	bool addBoundingBox)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;

	vertices.push_back(fvec3(0.0, 0.0, 0.0));
	colors.push_back(colorBottomLeft);
	vertices.push_back(fvec3(width, 0.0, 0.0));
	colors.push_back(colorBottomRight);
	vertices.push_back(fvec3(width, height, 0.0));
	colors.push_back(colorTopRight);
	vertices.push_back(fvec3(0.0, height, 0.0));
	colors.push_back(colorTopLeft);

	if (addBoundingBox)
	{
		ShapeMaker::addBoundingBoxVertices(&vertices, &colors);
	}

	return Shape(vertices, colors);
}

Shape ShapeMaker::makeTriangle(
	float sideLength,
	fvec4 colorTop,
	fvec4 colorBottomLeft,
	fvec4 colorBottomRight,
	bool addBoundingBox)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;

	float height = (sqrtf(3) / 2) * sideLength;

	vertices.push_back(fvec3(0, 2 * height / 3, 0));
	colors.push_back(colorTop);
	vertices.push_back(fvec3(-sideLength / 2, -height / 3, 0));
	colors.push_back(colorBottomLeft);
	vertices.push_back(fvec3(sideLength / 2, -height / 3, 0));
	colors.push_back(colorBottomRight);

	if (addBoundingBox)
	{
		ShapeMaker::addBoundingBoxVertices(&vertices, &colors);
	}

	return Shape(vertices, colors);
}

Shape ShapeMaker::makeCircle(
	int numberOfTriangles,
	fvec2 radius,
	fvec4 colorCenter,
	fvec4 colorBorder,
	bool addBoundingBox)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;

	float step = (2 * pi) / numberOfTriangles;

	vertices.push_back(fvec3(0));
	colors.push_back(colorCenter);

	for (int i = 0; i <= numberOfTriangles; i++)
	{
		float t = (float)i * step;
		float xx = radius.x * cos(t);
		float yy = radius.y * sin(t);
		vertices.push_back(fvec3(xx, yy, 0));
		colors.push_back(colorBorder);
	}

	if (addBoundingBox)
	{
		ShapeMaker::addBoundingBoxVertices(&vertices, &colors);
	}

	return Shape(vertices, colors);
}

Shape ShapeMaker::makeHermitCurve(
	string fileName,
	int numberOfTriangles,
	fvec4 colorTop,
	fvec4 colorBottom,
	bool addBoundingBox)
{
	vector<fvec3> vertices;
	vector<fvec4> colors;

	Shape curveShape = HermiteCurveMaker::makeHermiteCurve(
						   fileName,
						   numberOfTriangles,
						   colorTop,
						   colorBottom)
						   .front();

	if (addBoundingBox)
	{
		ShapeMaker::addBoundingBoxVertices(&curveShape.first, &curveShape.second);
	}

	return curveShape;
}

void ShapeMaker::addBoundingBoxVertices(vector<fvec3> *vertices, vector<fvec4> *colors)
{
	float minx = vertices->at(0).x; // Assumiamo che il primo elemento sia il minimo iniziale
	float miny = vertices->at(0).y; // Assumiamo che il primo elemento sia il minimo iniziale

	float maxx = vertices->at(0).x; // Assumiamo che il primo elemento sia il massimo iniziale
	float maxy = vertices->at(0).y; // Assumiamo che il primo elemento sia il massimo iniziale

	for (int i = 1; i < static_cast<int>(vertices->size()); i++)
	{
		if (vertices->at(i).x < minx)
		{
			minx = vertices->at(i).x;
		}
		if (vertices->at(i).x > maxx)
		{
			maxx = vertices->at(i).x;
		}

		if (vertices->at(i).y < miny)
		{
			miny = vertices->at(i).y;
		}

		if (vertices->at(i).y > maxy)
		{
			maxy = vertices->at(i).y;
		}
	}

	fvec4 boundingBoxMinObject = fvec4(minx, miny, 0.0, 1.0);
	fvec4 boundingBoxMaxObject = fvec4(maxx, maxy, 0.0, 1.0);

	// Add bounding box vertices to the vertices vector
	vertices->push_back(fvec3(boundingBoxMinObject.x, boundingBoxMinObject.y, 0));
	colors->push_back(fvec4(1, 1, 1, 1));
	vertices->push_back(fvec3(boundingBoxMaxObject.x, boundingBoxMinObject.y, 0));
	colors->push_back(fvec4(1, 1, 1, 1));
	vertices->push_back(fvec3(boundingBoxMaxObject.x, boundingBoxMaxObject.y, 0));
	colors->push_back(fvec4(1, 1, 1, 1));
	vertices->push_back(fvec3(boundingBoxMinObject.x, boundingBoxMaxObject.y, 0));
	colors->push_back(fvec4(1, 1, 1, 1));
}
