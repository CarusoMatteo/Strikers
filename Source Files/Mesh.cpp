#include "../Header Files/Mesh.h"

glm::mat4 Mesh::projectionMatrix;
bool Mesh::isWireframe = false;
bool Mesh::drawBoundingBox = false;

Mesh::Mesh(string vertexShaderName,
		   string fragmentShaderName,
		   bool shouldPrintLogs,
		   int numberOfPoints,
		   vector<fvec3> vertices,
		   vector<fvec4> colors,
		   GLenum drawMode,
		   ivec2 screenSize,
		   fvec3 scaleVector) : numberOfPoints(numberOfPoints), vertices(vertices), colors(colors), drawMode(drawMode), screenSize(screenSize), scaleVector(scaleVector)
{
	this->initBoundingBox();
	this->buildShader(vertexShaderName, fragmentShaderName, shouldPrintLogs);
	this->initVao();
	this->initVbos();
	this->initUniformReferences();
}

Mesh::~Mesh()
{
	glDeleteProgram(this->programId);
	glDeleteBuffers(1, &this->verticesVboAddress);
	glDeleteBuffers(1, &this->colorsVboAddress);
	glDeleteVertexArrays(1, &this->vaoAddress);
}

void Mesh::render(float rotationAngleDegrees, float timeElapsed)
{
	Renderer::render(this->programId,
					 &this->projectionMatrixUniformLocation, &Mesh::projectionMatrix,
					 &this->modelMatrixUniformLocation, &this->modelMatrix,
					 &this->screenSizeUniformLocation, this->screenSize,
					 &this->timeElapsedUniformLocation, timeElapsed,
					 &this->scaleVector, rotationAngleDegrees,
					 this->vaoAddress, this->drawMode, this->numberOfPoints);
}

void Mesh::buildShader(string vertexShaderName, string fragmentShaderName, bool shouldPrintLogs)
{
	// GLenum ErrorCheckValue = glGetError();
	this->programId = ShaderBuilder::buildShder(vertexShaderName.c_str(), fragmentShaderName.c_str(), shouldPrintLogs);
}

void Mesh::initVao()
{
	glGenVertexArrays(1, &this->vaoAddress);
	glBindVertexArray(this->vaoAddress);
}

void Mesh::initVbos()
{
	// Generates and makes active the VBO for the vertices
	glGenBuffers(1, &this->verticesVboAddress);
	glBindBuffer(GL_ARRAY_BUFFER, this->verticesVboAddress);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vec3), this->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	// Generates and makes active the VBO for the colors
	glGenBuffers(1, &this->colorsVboAddress);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorsVboAddress);
	glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);
}

void Mesh::initUniformReferences()
{
	this->projectionMatrixUniformLocation = glGetUniformLocation(this->programId, "projectionMatrix");
	this->modelMatrixUniformLocation = glGetUniformLocation(this->programId, "modelMatrix");

	this->timeElapsedUniformLocation = glGetUniformLocation(this->programId, "timeElapsed");
	this->screenSizeUniformLocation = glGetUniformLocation(this->programId, "screenSize");
}

void Mesh::initBoundingBox()
{
	// TODO: Method stub
}