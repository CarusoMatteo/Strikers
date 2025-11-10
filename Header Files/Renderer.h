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
		GLuint *isVisibleUniformLocation, bool isVisible,
		fvec3 *position, fvec3 *scaleVector, float rotationDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int pointCount);

	static void renderWithoutBB(
		unsigned int shaderProgramId,
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		GLuint *isVisibleUniformLocation, bool isVisible,
		fvec3 *position, fvec3 *scaleVector, float rotationDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int pointCount);

	static void renderCurveWithBB(
		unsigned int shaderProgramId,
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		GLuint *isVisibleUniformLocation, bool isVisible,
		fvec3 *position, fvec3 *scaleVector, float rotationDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int indicesCount,
		int *vertexCount);

	static void renderCurveWithoutBB(
		unsigned int shaderProgramId,
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		GLuint *isVisibleUniformLocation, bool isVisible,
		fvec3 *position, fvec3 *scaleVector, float rotationDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int indicesCount);

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
		GLuint *isVisibleUniformLocation, bool isVisible,
		fvec3 *position, fvec3 *scaleVector, float rotationDegrees,
		GLuint vaoAddress,
		GLenum renderMode,
		int pointCount,
		bool meshHasBB,
		bool isCurve,
		int *vertexCount);

	static void passUniforms(
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		GLuint *isVisibleUniformLocation, bool isVisible);

	static void applyTransformaiton(fmat4 *modelMatrix, fvec3 *position, fvec3 *scaleVector, float rotationDegrees, fvec3 *rotationAxis = new fvec3(0, 0, 1));
	static void drawMesh(GLuint vaoAddress, GLenum renderMode, int vertexCount, bool meshHasBB);
	static void drawCurveMesh(GLuint vaoAddress, GLenum renderMode, int indicesCount, bool meshHasBB, int *vertexCount);
	static void checkGLError();
};
