#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <GL/gl.h>

using std::string;

/**
 * @brief A utility class for building OpenGL shaders from source files.
 */
class ShaderBuilder
{
public:
	/**
	 * @brief Builds a shader program from vertex and fragment shader source files.
	 * 
	 * @param vertexfilename The path to the vertex shader source file.
	 * @param fragmentfilename The path to the fragment shader source file.
	 * @return GLuint The ID of the created shader program.
	 */
	static GLuint buildShder(const char *vertexfilename, const char *fragmentfilename);

private:
	ShaderBuilder() = default;
	~ShaderBuilder() = default;

	/// @brief Whether to print success logs during shader compilation and linking.
	static bool shouldPrintLogs;
	static char *readShaderSource(const char *shaderFile);
};
