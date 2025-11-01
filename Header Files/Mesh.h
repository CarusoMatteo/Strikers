#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ShaderBuilder.h"
#include "Renderer.h"

using std::string;
using std::vector;
using namespace glm;

class Mesh
{
public:
	Mesh(
		string vertexShaderName,
		string fragmentShaderName,
		bool shouldPrintLogs,
		int numberOfPoints,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		GLenum drawMode,
		ivec2 screenSize,
		fvec3 scaleVector);
	~Mesh();

	void render(float rotationAngleDegrees, float timeElapsed);
	static void setProjectionMatrix(mat4 projection)
	{
		Mesh::projectionMatrix = projection;
		// TODO?
		// Mesh::projectionMatrixUniformLocation = glGetUniformLocation(0, "projectionMatrix");
	}
	static bool *getIsWireframeRef()
	{
		return &isWireframe;
	}
	static bool shouldDrawWireframe()
	{
		return isWireframe;
	}
	static bool shouldDrawBoundingBox()
	{
		return drawBoundingBox;
	}

private:
	static bool isWireframe;
	static bool drawBoundingBox;

	// Shader compilation information

	GLuint programId;
	GLuint vaoAddress;
	GLuint verticesVboAddress;
	GLuint colorsVboAddress;

	int numberOfPoints;
	vector<fvec3> vertices;
	vector<fvec4> colors;

	GLenum drawMode;
	ivec2 screenSize;

	/// @brief Projection matrix to place object in world space.
	static mat4 projectionMatrix;
	GLuint projectionMatrixUniformLocation;

	mat4 modelMatrix;
	GLuint modelMatrixUniformLocation;

	fvec3 scaleVector;

	GLuint timeElapsedUniformLocation;
	GLuint screenSizeUniformLocation;

	vec4 boundingBoxMinObject;
	vec4 boundingBoxMaxObject;
	vec4 boundingBoxMinWorld;
	vec4 boundingBoxMaxWorld;

	void buildShader(string vertexShaderName, string fragmentShaderName, bool shouldPrintLogs);
	void initVao();
	void initVbos();
	void initUniformReferences();
	void initBoundingBox();
};
