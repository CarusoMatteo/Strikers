#include "../Header Files/Renderer.h"

#include <iostream>
using namespace std;

void Renderer::render(
	unsigned int shaderProgramId,
	GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
	GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
	GLuint *screenSizeUniformLocation, fvec2 windowSize,
	GLuint *currentTimeUniformLocation, float currentTime,
	fvec3 *position, fvec3 *scaleVector, float rotationAngleDegrees,
	GLuint vaoAddress,
	GLenum renderMode,
	int vertexCount)
{
	Renderer::renderWithUniforms(shaderProgramId, projectionMatrixUniformLocation, projectionMatrix, modelMatrixUniformLocation, modelMatrix, screenSizeUniformLocation, windowSize, currentTimeUniformLocation, currentTime);
	Renderer::applyTransformaiton(modelMatrix, scaleVector, rotationAngleDegrees);
	Renderer::renderWithBoundingBox(vaoAddress, renderMode, vertexCount);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cout << "GL Error: " << err << std::endl;
		throw std::runtime_error("OpenGL error occurred during rendering.");
	}
}

void Renderer::renderWithUniforms(unsigned int shaderProgramId,
								  GLuint *projectionMatrixUniformLocation, fmat4 *projectionMatrix,
								  GLuint *modelMatrixUniformLocation, fmat4 *modelMatrix,
								  GLuint *screenSizeUniformLocation, fvec2 windowSize,
								  GLuint *currentTimeUniformLocation, float currentTime)
{
	// Enable selected shader program
	glUseProgram(shaderProgramId);

	// Pass the projection matrix to the "projectionMatrix" uniform
	glUniformMatrix4fv(*projectionMatrixUniformLocation, 1, GL_FALSE, value_ptr(*projectionMatrix));
	// Pass the model matrix to the "modelMatrix" uniform
	glUniformMatrix4fv(*modelMatrixUniformLocation, 1, GL_FALSE, value_ptr(*modelMatrix));

	// if (resolution.x > 0.0f && resolution.y > 0.0f) Should always be valid?
	// Pass the resolution to the "windowSize" uniform
	glUniform2f(*screenSizeUniformLocation, windowSize.x, windowSize.y);

	// Pass the current time to the "currentTime" uniform
	// if (currentTime > 0.0f)
	glUniform1f(*currentTimeUniformLocation, currentTime);
}

void Renderer::applyTransformaiton(fmat4 *modelMatrix, fvec3 *scaleVector, float rotationAngleDegrees)
{
	*modelMatrix = fmat4(1.0f);
	*modelMatrix = translate(*modelMatrix, fvec3(0));
	*modelMatrix = rotate(*modelMatrix, glm::radians(rotationAngleDegrees), fvec3(0, 0, 1));
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

void Renderer::renderWithBoundingBox(GLuint vaoAddress, GLenum renderMode, int vertexCount)
{
	if (MeshBB::shouldDrawWireframe())
	{
		// Draw in wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		// Otherwise, fill the faces in solid mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Bind the Vertex Array Object (VAO) of the shape, which contains the vertex data to be drawn
	glBindVertexArray(vaoAddress);

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
