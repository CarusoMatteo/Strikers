#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using std::string;
using std::vector;
using namespace glm;

class Mesh
{
public:
	Mesh(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);
	~Mesh();

	static void setProjectionMatrix(fmat4 projection)
	{
		Mesh::projectionMatrix = projection;
	}
	static bool *getIsWireframeRef()
	{
		return &isWireframe;
	}
	static bool shouldDrawWireframe()
	{
		return isWireframe;
	}

	virtual void render(float currentTime, float rotationAngleDegrees = 0.0f);
	void updateScreenSize(ivec2 newScreenSize)
	{
		this->windowSize = newScreenSize;
	}

	fvec3 getPosition() const
	{
		return this->position;
	}
	void setPosition(fvec3 newPosition)
	{
		this->position = newPosition;
	}
	void setIsVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}

protected:
	static bool isWireframe;

	// Shader compilation information

	GLuint programId;
	GLuint vaoAddress;
	GLuint verticesVboAddress;
	GLuint colorsVboAddress;

	vector<fvec3> vertices;
	vector<fvec4> colors;

	GLenum drawMode;
	ivec2 windowSize;

	/// @brief Projection matrix to place object in world space.
	static fmat4 projectionMatrix;
	GLuint projectionMatrixUniformLocation;

	fmat4 modelMatrix;
	GLuint modelMatrixUniformLocation;

	fvec3 position;
	fvec3 scaleVector;

	float creationTime;
	GLuint creationTimeUniformLocation;
	bool isVisible = true;
	GLuint isVisibleUniformLocation;

	GLuint currentTimeUniformLocation;
	GLuint screenSizeUniformLocation;

	void buildShader(string vertexShaderName, string fragmentShaderName);
	void initVao();
	void initVbos();
	void initUniformReferences();
};
