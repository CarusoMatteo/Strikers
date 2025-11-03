#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <GL/gl.h>

using std::string;

class ShaderBuilder
{
public:
	static GLuint buildShder(const char *vertexfilename, const char *fragmentfilename, bool shouldPrintLogs);

private:
	ShaderBuilder() = default;
	~ShaderBuilder() = default;

	static char *readShaderSource(const char *shaderFile);
};
