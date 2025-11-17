#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform bool isVisible;

void main()
{
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos, 1.0);


	// Set the alpha to 0.0 if !isVisible, otherwise keep original alpha
	ourColor = vec4(aColor.rgb, isVisible ? aColor.a : 0.0);
}
