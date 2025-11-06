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

vec4 fadeColor(vec4 color)
{
	float timeToLiveSeconds = 0.5;

	float lifeTime = currentTime - creationTime;
	float alpha = 1.0 - (lifeTime / timeToLiveSeconds);
	alpha = clamp(alpha, 0.0, 1.0);
	return vec4(color.r, color.g, color.b, color.a * alpha);
}

void main()
{
	/*
	 * Transformation of the vertices from the object's local coordinate system (apos),
	 * to the world coordinate system (premultiplication by Model),
	 * and subsequently projected into the cube centered at the origin with side length 2,
	 * with x, y, z ranging from -1 to 1 (premultiplication by the Projection matrix)
	 */
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos, 1.0);
	ourColor = fadeColor(aColor);
}
