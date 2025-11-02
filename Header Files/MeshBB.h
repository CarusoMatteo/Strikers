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

class MeshBB
{
public:
	MeshBB(
		string vertexShaderName,
		string fragmentShaderName,
		bool shouldPrintLogs,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		GLenum drawMode,
		ivec2 screenSize,
		fvec3 scaleVector,
		mat4 modelMatrix);
	~MeshBB();

	void render(float currentTime, float rotationAngleDegrees = 0.0f);
	static void setProjectionMatrix(mat4 projection)
	{
		MeshBB::projectionMatrix = projection;
	}
	static bool *getIsWireframeRef()
	{
		return &isWireframe;
	}
	static bool shouldDrawWireframe()
	{
		return isWireframe;
	}
	static bool *shouldDrawBoundingBoxRef()
	{
		return &drawBoundingBox;
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

	GLuint currentTimeUniformLocation;
	GLuint screenSizeUniformLocation;

	fvec4 boundingBoxMinObject;
	fvec4 boundingBoxMaxObject;
	fvec4 boundingBoxMinWorld;
	fvec4 boundingBoxMaxWorld;

	void buildShader(string vertexShaderName, string fragmentShaderName, bool shouldPrintLogs);
	void initVao();
	void initVbos();
	void initUniformReferences();
	void initBoundingBox();

	void updateBoundingBoxWorld();
};
