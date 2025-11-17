#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform float creationTime;
uniform float currentTime;

// Fades the color based on the lifetime of the explosion.
// Returns the faded version of the input color.
vec4 fadeColor(vec4 color)
{
	// How  long the explosion lasts in seconds
	float timeToLiveSeconds = 0.5;

	float lifeTime = currentTime - creationTime;
	float alpha = 1.0 - (lifeTime / timeToLiveSeconds);
	alpha = clamp(alpha, 0.0, 1.0);
	return vec4(color.r, color.g, color.b, color.a * alpha);
}

void main()
{
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos, 1.0);
	ourColor = fadeColor(aColor);
}
