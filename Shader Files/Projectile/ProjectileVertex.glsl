#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform float creationTime;
uniform float currentTime;

// Returns a degree value [0,360) based on creationTime and currentTime.
float degreeFromTime()
{
	return mod(creationTime + currentTime, 360.0);
}

void main()
{
	// Projectile rotation speed
	float rotationSpeed = 500.0;

	float angle = radians(degreeFromTime()) * rotationSpeed;
	// Rotation matrix around the Z axis
	mat4 rotationMatrix = mat4(cos(angle), -sin(angle), 0.0, 0.0, sin(angle), cos(angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	gl_Position = projectionMatrix * modelMatrix * rotationMatrix * vec4(aPos, 1.0);
	ourColor = aColor;
}
