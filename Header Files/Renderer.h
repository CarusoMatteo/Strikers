#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

#include "MeshBB.h"

using namespace glm;
using std::vector;

class Renderer
{
public:
	static void render(unsigned int shaderProgramId,
					   GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
					   GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
					   GLuint *screenSizeUniformLocation, fvec2 windowSize,
					   GLuint *currentTimeUniformLocation, float currentTime,
					   fvec3 *position, fvec3 *scaleVector, float rotationAngleDegrees,
					   GLuint vaoAddress,
					   GLenum renderMode,
					   int vertexCount);

private:
	Renderer() = default;
	~Renderer() = default;

	static void renderWithUniforms(unsigned int shaderProgramId,
								   GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
								   GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
								   GLuint *screenSizeUniformLocation, fvec2 windowSize,
								   GLuint *currentTimeUniformLocation, float currentTime);

	static void applyTransformaiton(fmat4 *modelMatrix, fvec3 *scaleVector, float rotationAngleDegrees);

	static void renderWithBoundingBox(GLuint vaoAddress, GLenum renderMode, int numberOfTriangles);
};
