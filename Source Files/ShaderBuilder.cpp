#include "../Header Files/ShaderBuilder.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>

GLuint ShaderBuilder::buildShder(char *vertexfilename, char *fragmentfilename, bool shouldPrintLogs)
{
	int success;
	char infoLog[512];

	// Create shader executables
	// Read the Vertex Shader code
	GLchar *VertexShader = ShaderBuilder::readShaderSource(vertexfilename);
	// Print the VERTEX SHADER CODE to the console if requested
	if (shouldPrintLogs && VertexShader)
	{
		std::cout << VertexShader << std::endl;
	}

	// Generate an identifier for the vertex shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	// Associate the vertex shader code with the identifier
	glShaderSource(vertexShaderId, 1, (const char **)&VertexShader, NULL);
	// Compile the Vertex Shader
	glCompileShader(vertexShaderId);

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "Error: Vertex shader compilation failed.\n"
				  << infoLog << std::endl;
	}

	// Read the Fragment Shader code
	const GLchar *FragmentShader = ShaderBuilder::readShaderSource(fragmentfilename);
	// Print the FRAGMENT SHADER CODE to the console if requested
	if (shouldPrintLogs && FragmentShader)
	{
		std::cout << FragmentShader << std::endl;
	}

	// Generate an identifier for the FRAGMENT shader
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, (const char **)&FragmentShader, NULL);
	// Compile the FRAGMENT Shader
	glCompileShader(fragmentShaderId);

	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "Error: Fragment shader compilation failed.\n"
				  << infoLog << std::endl;
	}

	// Create an identifier for a program and attach the two compiled shaders to it
	GLuint programId = glCreateProgram();

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	return programId;
}

#pragma warning(disable : 6386)
#pragma warning(disable : 4996)
char *ShaderBuilder::readShaderSource(const char *shaderFile)
{
	FILE *fp = fopen(shaderFile, "rb");

	if (fp == NULL)
	{
		return NULL;
	}

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char *buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}
