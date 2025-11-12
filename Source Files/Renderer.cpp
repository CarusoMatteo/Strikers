#include "../Header Files/Renderer.h"

#include "../Header Files/Mesh.h"
#include "../Header Files/MeshBB.h"

#pragma region Public access methods

void Renderer::renderWithBB(
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
	int pointCount)
{
	bool meshHasBB = false;
	bool isCurve = false;
	int *vertexCount = nullptr;

	Renderer::render(
		shaderProgramId,
		projectionMatrixUniformLocation, projectionMatrix,
		modelMatrixUniformLocation, modelMatrix,
		screenSizeUniformLocation, windowSize,
		creationTimeUniformLocation, creationTime,
		currentTimeUniformLocation, currentTime,
		isVisibleUniformLocation, isVisible,
		position, scaleVector, rotationDegrees,
		vaoAddress,
		renderMode,
		pointCount,
		meshHasBB,
		isCurve,
		vertexCount);
}

void Renderer::renderWithoutBB(
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
	int pointCount)
{
	bool meshHasBB = false;
	bool isCurve = false;
	int *vertexCount = nullptr;

	Renderer::render(
		shaderProgramId,
		projectionMatrixUniformLocation, projectionMatrix,
		modelMatrixUniformLocation, modelMatrix,
		screenSizeUniformLocation, windowSize,
		creationTimeUniformLocation, creationTime,
		currentTimeUniformLocation, currentTime,
		isVisibleUniformLocation, isVisible,
		position, scaleVector, rotationDegrees,
		vaoAddress,
		renderMode,
		pointCount,
		meshHasBB,
		isCurve,
		vertexCount);
}

void Renderer::renderCurveWithBB(
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
	int *vertexCount)
{
	bool meshHasBB = true;
	bool isCurve = true;

	Renderer::render(
		shaderProgramId,
		projectionMatrixUniformLocation, projectionMatrix,
		modelMatrixUniformLocation, modelMatrix,
		screenSizeUniformLocation, windowSize,
		creationTimeUniformLocation, creationTime,
		currentTimeUniformLocation, currentTime,
		isVisibleUniformLocation, isVisible,
		position, scaleVector, rotationDegrees,
		vaoAddress,
		renderMode,
		indicesCount,
		meshHasBB,
		isCurve,
		vertexCount);
}

void Renderer::renderCurveWithoutBB(
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
	int indicesCount)
{
	bool meshHasBB = false;
	bool isCurve = true;
	int *vertexCount = nullptr;

	Renderer::render(
		shaderProgramId,
		projectionMatrixUniformLocation, projectionMatrix,
		modelMatrixUniformLocation, modelMatrix,
		screenSizeUniformLocation, windowSize,
		creationTimeUniformLocation, creationTime,
		currentTimeUniformLocation, currentTime,
		isVisibleUniformLocation, isVisible,
		position, scaleVector, rotationDegrees,
		vaoAddress,
		renderMode,
		indicesCount,
		meshHasBB,
		isCurve,
		vertexCount);
}

#pragma endregion

void Renderer::render(
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
	int *vertexCount)
{
	// Enable selected shader program
	glUseProgram(shaderProgramId);

	Renderer::passUniforms(
		projectionMatrixUniformLocation, projectionMatrix,
		modelMatrixUniformLocation, modelMatrix,
		screenSizeUniformLocation, windowSize,
		creationTimeUniformLocation, creationTime,
		currentTimeUniformLocation, currentTime,
		isVisibleUniformLocation, isVisible);
	Renderer::applyTransformaiton(modelMatrix, position, scaleVector, rotationDegrees);
	if (!isCurve)
		Renderer::drawMesh(vaoAddress, renderMode, pointCount, meshHasBB);
	else
		Renderer::drawCurveMesh(vaoAddress, renderMode, pointCount, meshHasBB, vertexCount);
	Renderer::checkGLError();
}

void Renderer::passUniforms(
	GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
	GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
	GLuint *screenSizeUniformLocation, fvec2 windowSize,
	GLuint *creationTimeUniformLocation, float creationTime,
	GLuint *currentTimeUniformLocation, float currentTime,
	GLuint *isVisibleUniformLocation, bool isVisible)
{
	// Pass the projection matrix to the "projectionMatrix" uniform
	glUniformMatrix4fv(*projectionMatrixUniformLocation, 1, GL_FALSE, value_ptr(*projectionMatrix));
	// Pass the model matrix to the "modelMatrix" uniform
	glUniformMatrix4fv(*modelMatrixUniformLocation, 1, GL_FALSE, value_ptr(*modelMatrix));

	// Pass the resolution to the "windowSize" uniform
	glUniform2f(*screenSizeUniformLocation, windowSize.x, windowSize.y);

	// Pass the creation time to the "creationTime" uniform
	glUniform1f(*creationTimeUniformLocation, creationTime);

	// Pass the current time to the "currentTime" uniform
	glUniform1f(*currentTimeUniformLocation, currentTime);

	// Pass the visibility status to the "isVisible" uniform
	glUniform1i(*isVisibleUniformLocation, isVisible ? 1 : 0);
}

void Renderer::applyTransformaiton(fmat4 *modelMatrix, fvec3 *position, fvec3 *scaleVector, float rotationDegrees, fvec3 *rotationAxis)
{
	*modelMatrix = fmat4(1.0f);
	*modelMatrix = translate(*modelMatrix, *position);
	*modelMatrix = rotate(*modelMatrix, glm::radians(rotationDegrees), *rotationAxis);
	*modelMatrix = scale(*modelMatrix, *scaleVector);

	/*
	 * // Se richiesto, restituisce matrice senza scala tramite puntatore
	 * // Comodo se ho un'oggetto che ha la stessa posizione e rotazione ma scala diversa (es. laser).
	 * If requested, return matrix without scale via pointer
	 * Useful if I have an object that has the same position and rotation but different scale (e.g. laser).
	 * 	if (restituisciSenzaScala && outModelNoScale != nullptr)
	 * 	{
	 * 		fmat4 modelNoScale = fmat4(1.0f);
	 * 		modelNoScale = translate(modelNoScale, fvec3(forma->position.x + dx, forma->position.y + dy, 0.0f));
	 * 		modelNoScale = rotate(modelNoScale, fradians(angoloUsato), fvec3(0, 0, 1));
	 * 		// nessuna scala qui
	 * 		*outModelNoScale = modelNoScale;
	 * 	}
	 */
}

void Renderer::drawMesh(GLuint vaoAddress, GLenum renderMode, int vertexCount, bool meshHasBB)
{
	if (Mesh::shouldDrawWireframe())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Bind the Vertex Array Object (VAO) of the shape, which contains the vertex data to be drawn
	glBindVertexArray(vaoAddress);

	if (meshHasBB)
	{
		/*
		 * Draw the vertices of the shape as specified by renderMode,
		 * starting from the first vertex (0), for (numVertices - 4) vertices in total
		 * The subtraction of 4 is to exclude the vertices of the bounding box.
		 */
		glDrawArrays(renderMode, 0, vertexCount - 4);

		if (MeshBB::shouldDrawBoundingBox())
		{
			// Draw the bounding box with a line loop connecting the last 4 vertices
			glDrawArrays(GL_LINE_LOOP, vertexCount - 4, 4);
		}
	}
	else
	{
		// Draw the vertices of the shape as specified by renderMode,
		// starting from the first vertex (0), for vertexCount vertices in total
		glDrawArrays(renderMode, 0, vertexCount);
	}
}

void Renderer::drawCurveMesh(GLuint vaoAddress, GLenum renderMode, int indicesCount, bool meshHasBB, int *vertexCount)
{
	// Bind the Vertex Array Object (VAO) of the shape, which contains the vertex data to be drawn
	glBindVertexArray(vaoAddress);

	if (meshHasBB)
	{
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

		if (MeshBB::shouldDrawBoundingBox())
		{
			if (vertexCount == nullptr)
			{
				throw std::runtime_error("vertexCount pointer is null when trying to draw curve's bounding box.");
			}

			// Draw the bounding box with aline loop connecting the last 4 indices
			// Draw the bounding box with a line loop connecting the last 4 vertices
			glDrawArrays(GL_LINE_LOOP, *vertexCount - 4, 4);
		}
	}
	else
	{
		// Draw the vertices of the shape as specified by renderMode,
		// starting from the first vertex (0), for vertexCount vertices in total
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Renderer::checkGLError()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "OpenGL Error: " << error << std::endl;
		throw std::runtime_error("OpenGL encountered an error.");
	}
}