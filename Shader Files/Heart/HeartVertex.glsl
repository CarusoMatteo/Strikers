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
uniform float creationTime; // Used as pulse speed
uniform float currentTime;

float oscillate(float minVal, float maxVal, float speed)
{
	float amplitude = (maxVal - minVal) / 2.0;
	float midPoint = minVal + amplitude;
	return midPoint + amplitude * sin(currentTime * speed);
}

void main()
{
	/*
	 * Transformation of the vertices from the object's local coordinate system (apos),
	 * to the world coordinate system (premultiplication by Model),
	 * and subsequently projected into the cube centered at the origin with side length 2,
	 * with x, y, z ranging from -1 to 1 (premultiplication by the Projection matrix)
	 */
	float oscillationSpeed = creationTime * 25.0 + 5.0; // Creation time used as "missingHealthPercentage", always between 0..1
	float minScale = 0.9;
	float maxScale = 1.1;
	vec3 scaleVector = vec3(abs(oscillate(minScale, maxScale, oscillationSpeed))) + 1.0 * creationTime;
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos * scaleVector, 1.0);

	vec3 interpolatedColor = mix(aColor.rgb, vec3(0.5), creationTime);
	ourColor.rgb = interpolatedColor; // set ourColor to the input color we got from the vertex data
	// ourColor = aColor;
	ourColor.a = creationTime == 1 ? 0.0 : aColor.a;
}
