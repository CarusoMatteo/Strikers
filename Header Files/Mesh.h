#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using std::string;
using std::vector;
using namespace glm;

/**
 * @brief Class representing a mesh with a shader associated to it.
 */
class Mesh
{
public:
	Mesh() = default;
	Mesh(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		float rotationDegrees,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);
	~Mesh();

	/// @brief Renders the mesh using the static Renderer class.
	virtual void render(float currentTime);
	static void setProjectionMatrix(fmat4 projection)
	{
		Mesh::projectionMatrix = projection;
	}
	static bool *getIsWireframeRef()
	{
		return &isWireframe;
	}
	static bool shouldDrawWireframe()
	{
		return isWireframe;
	}
	void updateScreenSize(ivec2 newScreenSize)
	{
		this->windowSize = newScreenSize;
	}
	fvec3 getPosition() const
	{
		return this->position;
	}
	void setPosition(fvec3 newPosition)
	{
		this->position = newPosition;
	}
	void setCreationTime(float creationTime)
	{
		this->creationTime = creationTime;
	}
	void setIsVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}
	ivec2 getWindowSize() const
	{
		return this->windowSize;
	}

protected:
	static bool isWireframe;

	// Shader compilation information

	GLuint programId;
	GLuint vaoAddress;
	GLuint verticesVboAddress;
	GLuint colorsVboAddress;

	vector<fvec3> vertices;
	vector<fvec4> colors;

	GLenum drawMode;
	ivec2 windowSize;

	/// @brief Projection matrix to place object in world space. The same for all meshes.
	static fmat4 projectionMatrix;
	GLuint projectionMatrixUniformLocation;

	/// @brief Model matrix of this mesh.
	fmat4 modelMatrix;
	GLuint modelMatrixUniformLocation;

	/// @brief Position of this mesh in world space.
	fvec3 position;
	/// @brief Rotation of this mesh in degrees.
	float rotationDegrees;
	/// @brief Scale vector of this mesh.
	fvec3 scaleVector;

	/// @brief Time of creation of mesh. Used for some animation.
	float creationTime;
	GLuint creationTimeUniformLocation;
	/// @brief Whether the mesh is visible or not. Used for toggling visibility in shaders.
	bool isVisible = true;
	GLuint isVisibleUniformLocation;

	GLuint currentTimeUniformLocation;
	GLuint screenSizeUniformLocation;

	/**
	 * @brief Builds the shader program from vertex and fragment shader files.
	 * @param vertexShaderName Name of the vertex shader file.
	 * @param fragmentShaderName Name of the fragment shader file.
	 */
	void buildShader(string vertexShaderName, string fragmentShaderName);
	///@brief Initializes the VAO for this mesh.
	void initVao();
	/// @brief Initializes the VBOs for this mesh.
	void initVbos();
	/// @brief Initializes the uniform references locations for this mesh.
	void initUniformReferences();
};
