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
	Mesh(string vertexShaderName, string fragmentShaderName, bool shouldPrintLogs);
	~Mesh();

	void render(float rotationAngleDegrees);
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

	/// @brief Position in world space.
	vec3 position;
	int numberOfPoints;
	vector<fvec3> vertices;
	vector<fvec4> colors;

	GLenum drawMode;
	vec2 screenSize;

	/// @brief Projection matrix to place object in world space.
	static mat4 projectionMatrix;
	GLint projectionMatrixUniformLocation;

	mat4 modelMatrix;
	GLint modelMatrixUniformLocation;

	vec3 scaleVector;

	// GLint timeElapsedUniformLocation;
	// GLint screenSizeUniformLocation;

	vec4 boundingBoxMinObject;
	vec4 boundingBoxMaxObject;
	vec4 boundingBoxMinWorld;
	vec4 boundingBoxMaxWorld;

	void Mesh::buildShader(string vertexShaderName, string fragmentShaderName, bool shouldPrintLogs);
	void Mesh::initVao();
	void Mesh::initVbos();
	void Mesh::initUniformReferences();
};
