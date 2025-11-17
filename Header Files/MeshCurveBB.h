#pragma once
#include "MeshBB.h"

#include <string>
#include <array>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using std::array;
using std::string;
using std::vector;
using namespace glm;

/**
 * @brief Class representing a Hermite Curve Mesh with a bounding box for collision detection.
 */
class MeshCurveBB : public MeshBB
{
public:
	MeshCurveBB(
		string vertexShaderName,
		string fragmentShaderName,
		vector<fvec3> vertices,
		vector<fvec4> colors,
		fvec3 position,
		float rotationDegrees,
		fvec3 scaleVector,
		GLenum drawMode,
		ivec2 windowSize);

	/// @brief Triangulates the given control points into vertices and colors for rendering the curve.
	void triangulate(
		vector<fvec3> *vertices,
		vector<fvec4> *colors);

	void render(float currentTime) override;

private:
	vector<unsigned int> indices;

	/// @brief Element Buffer Object for the vertices indices
	GLuint indicesEboAddress;

	/// @brief Initializes vertices VBO, colors VBO and indices EBO for this mesh.
	void initVbos();
};
