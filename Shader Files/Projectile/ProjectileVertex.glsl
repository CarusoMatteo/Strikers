#version 330 core

// The position variable has attribute position 0
layout (location = 0) in vec3 aPos;
// The color variable has attribute position 1
layout (location = 1) in vec4 aColor;

// Output a color to the fragment shader
out vec4 ourColor;
// Uniform, stays the same for every vertex of the primitive 
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform float creationTime;
uniform float currentTime;

float degreeFromTime()
{
	return mod(creationTime + currentTime, 360.0);
}

void main()
{
	float rotationSpeed = 500.0;
	/*
	 * Transformation of the vertices from the object's local coordinate system (apos),
	 * to the world coordinate system (premultiplication by Model),
	 * and subsequently projected into the cube centered at the origin with side length 2,
	 * with x, y, z ranging from -1 to 1 (premultiplication by the Projection matrix)
	 */
	float angle = radians(degreeFromTime()) * rotationSpeed;
	mat4 rotationMatrix = mat4(cos(angle), -sin(angle), 0.0, 0.0, sin(angle), cos(angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	gl_Position = projectionMatrix * modelMatrix * rotationMatrix * vec4(aPos, 1.0);
	ourColor = aColor; // set ourColor to the input color we got from the vertex data
}
