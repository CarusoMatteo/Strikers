#pragma once

#include <string>
#include <glad/glad.h>

using std::string;

class ShaderBuilder
{
public:
	static GLuint buildShder(char *vertexfilename, char *fragmentfilename, bool shouldPrintLogs);

private:
	ShaderBuilder() = default;
	~ShaderBuilder() = default;

	static char *readShaderSource(const char *shaderFile);
};
