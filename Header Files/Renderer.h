#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

using namespace glm;
using std::vector;

class Mesh;
class MeshBB;

class Renderer
{
public:
	static void renderWithBB(
		unsigned int shaderProgramId,
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		fvec3 *position, fvec3 *scaleVector, float rotationAngleDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int vertexCount);

	static void renderWithoutBB(
		unsigned int shaderProgramId,
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		fvec3 *position, fvec3 *scaleVector, float rotationAngleDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int vertexCount);

private:
	Renderer() = default;
	~Renderer() = default;

	static void render(
		unsigned int shaderProgramId,
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		fvec3 *position, fvec3 *scaleVector, float rotationAngleDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int vertexCount,
		bool checkBB);

	static void passUniforms(
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime);

	static void applyTransformaiton(fmat4 *modelMatrix, fvec3 *position, fvec3 *scaleVector, float rotationAngleDegrees, fvec3 *rotationAxis = new fvec3(0, 0, 1));
	static void drawMesh(GLuint vaoAddress, GLenum renderMode, int vertexCount, bool meshHasBB);
	static void checkGLError();
};
