#pragma once

#include <string>
#include <glad/glad.h>

using std::string;

class ShaderBuilder
{
public:
	static GLuint buildShder(string vertexfilename, string fragmentfilename, bool shouldPrintLogs);

private:
	ShaderBuilder() = default;
	~ShaderBuilder() = default;
};
