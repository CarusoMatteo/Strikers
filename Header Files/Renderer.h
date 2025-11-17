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

/// @brief Static class that provides rendering utilities.
class Renderer
{
public:
	/// @brief Renders a mesh that has a bounding box.
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
	/// @brief Renders a mesh that doesn't have a bounding box.
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
	/// @brief Renders a Hermite curve mesh that has a bounding box.
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
	/// @brief Renders a Hermite curve mesh that doesn't have a bounding box.
	/// Warning: Functionality unused and untested.
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
	/**
	 * @brief Renders a mesh.
	 * @param shaderProgramId The shader program ID to use for rendering.
	 * @param projectionMatrixUniformLocation The uniform location for the projection matrix in this shader program.
	 * @param projectionMatrix The projection matrix to use for rendering.
	 * @param modelMatrixUniformLocation The uniform location for the model matrix in this shader program.
	 * @param modelMatrix The model matrix to use for rendering.
	 * @param screenSizeUniformLocation The uniform location for the screen size in this shader program.
	 * @param windowSize The current window size.
	 * @param creationTimeUniformLocation The uniform location for the creation time in this shader program.
	 * @param creationTime The creation time of the mesh to render.
	 * @param currentTimeUniformLocation The uniform location for the current time in this shader program.
	 * @param currentTime The current time.
	 * @param isVisibleUniformLocation The uniform location for the visibility flag in this shader program.
	 * @param isVisible Whether the mesh is visible or not.
	 * @param position The position of the mesh.
	 * @param scaleVector The scale vector of the mesh.
	 * @param rotationDegrees The rotation of the mesh in degrees.
	 * @param vaoAddress The VAO address of the mesh to render.
	 * @param renderMode The OpenGL render mode to use.
	 * @param pointCount The number of points to render.
	 * @param meshHasBB Whether the mesh has a bounding box.
	 * @param isCurve Whether the mesh is a curve.
	 * @param vertexCount The number of vertices in the mesh (used for curve meshes).
	 */
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

	/// @brief Passes uniform variables to the shader program.
	static void passUniforms(
		GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
		GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
		GLuint *screenSizeUniformLocation, fvec2 windowSize,
		GLuint *creationTimeUniformLocation, float creationTime,
		GLuint *currentTimeUniformLocation, float currentTime,
		GLuint *isVisibleUniformLocation, bool isVisible);

	/// @brief Applies transformation to the model matrix.
	static void applyTransformaiton(fmat4 *modelMatrix, fvec3 *position, fvec3 *scaleVector, float rotationDegrees, fvec3 *rotationAxis = new fvec3(0, 0, 1));
	/// @brief Draws a mesh.
	static void drawMesh(GLuint vaoAddress, GLenum renderMode, int vertexCount, bool meshHasBB);
	/// @brief Draws a Hermite curve mesh.
	static void drawCurveMesh(GLuint vaoAddress, GLenum renderMode, int indicesCount, bool meshHasBB, int *vertexCount);
	/// @brief Checks for OpenGL errors and throws an exception if any are found.
	static void checkGLError();
};
