#include "../Header Files/MeshCurve.h"

MeshCurve::MeshCurve(string vertexShaderName,
					 string fragmentShaderName,
					 vector<fvec3> vertices,
					 vector<fvec4> colors,
					 fvec3 position,
					 fvec3 scaleVector,
					 GLenum drawMode,
					 ivec2 windowSize) : Mesh(vertexShaderName,
											  fragmentShaderName,
											  vertices,
											  colors,
											  position,
											  scaleVector,
											  drawMode,
											  windowSize)
{
}

void MeshCurve::render(float currentTime, float rotationAngleDegrees)
{
}
