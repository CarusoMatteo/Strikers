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
// Used as missingHealthPercentage [0,1], didn't create a new uniform for time constraints.
uniform float creationTime;
uniform float currentTime;

float oscillate(float minVal, float maxVal, float speed)
{
	float amplitude = (maxVal - minVal) / 2.0;
	float midPoint = minVal + amplitude;
	return midPoint + amplitude * sin(currentTime * speed);
}

void main()
{
	float minScale = 0.9;
	float maxScale = 1.1;

	float oscillationSpeed = creationTime * 25.0 + 5.0;
	vec3 scaleVector = vec3(abs(oscillate(minScale, maxScale, oscillationSpeed))) + 1.0 * creationTime;
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos * scaleVector, 1.0);

	vec3 interpolatedColor = mix(aColor.rgb, vec3(0.5), creationTime);
	ourColor.rgb = interpolatedColor;
	ourColor.a = creationTime == 1 ? 0.0 : aColor.a;
}
