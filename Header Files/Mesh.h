#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

using std::vector;
using namespace glm;

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	void render();
	static void setProjectionMatrix(mat4 projection)
	{
		Mesh::projectionMatrix = projection;
	}
	static bool *getIsWireframeRef()
	{
		return &isWireframe;
	}

private:
	GLuint programId;
	int numberOfTriangles;
	vector<vec3> *vertices;
	vector<vec4> *colors;
	GLenum drawMode;
	vec2 *screenSize;

	static bool isWireframe;

	static mat4 projectionMatrix;
	GLint projectionMatrixUniformLocation;
	mat4 *modelMatrix;
	GLint modelMatrixUniformLocation;
	mat4 *scaleMatrix;

	// GLint timeElapsedUniformLocation;
	// GLint screenSizeUniformLocation;

	vec4 *boundingBoxMinObject;
	vec4 *boundingBoxMaxObject;
	vec4 *boundingBoxMinWorld;
	vec4 *boundingBoxMaxWorld;

	void buildShader();
	void initVao();
	void initVbos();
};
