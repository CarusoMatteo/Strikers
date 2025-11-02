#include "../Header Files/MeshBB.h"

glm::fmat4 MeshBB::projectionMatrix;
bool MeshBB::isWireframe = false;
bool MeshBB::drawBoundingBox = false;

MeshBB::MeshBB(string vertexShaderName,
			   string fragmentShaderName,
			   bool shouldPrintLogs,
			   vector<fvec3> vertices,
			   vector<fvec4> colors,
			   GLenum drawMode,
			   ivec2 windowSize,
			   fvec3 scaleVector,
			   fmat4 modelMatrix) : vertices(vertices), colors(colors),
								   drawMode(drawMode),
								   windowSize(windowSize),
								   scaleVector(scaleVector),
								   modelMatrix(modelMatrix)
{
	this->buildShader(vertexShaderName, fragmentShaderName, shouldPrintLogs);
	this->initBoundingBox();
	this->initVao();
	this->initVbos();
	this->initUniformReferences();
}

MeshBB::~MeshBB()
{
	glDeleteProgram(this->programId);
	glDeleteBuffers(1, &this->verticesVboAddress);
	glDeleteBuffers(1, &this->colorsVboAddress);
	glDeleteVertexArrays(1, &this->vaoAddress);
}

void MeshBB::render(float currentTime, float rotationAngleDegrees)
{
	Renderer::render(this->programId,
					 &this->projectionMatrixUniformLocation, &MeshBB::projectionMatrix,
					 &this->modelMatrixUniformLocation, &this->modelMatrix,
					 &this->screenSizeUniformLocation, this->windowSize,
					 &this->currentTimeUniformLocation, currentTime,
					 &this->scaleVector, rotationAngleDegrees,
					 this->vaoAddress, this->drawMode, static_cast<int>(this->vertices.size()));
}

void MeshBB::buildShader(string vertexShaderName, string fragmentShaderName, bool shouldPrintLogs)
{
	this->programId = ShaderBuilder::buildShder(vertexShaderName.c_str(), fragmentShaderName.c_str(), shouldPrintLogs);
}

void MeshBB::initVao()
{
	glGenVertexArrays(1, &this->vaoAddress);
	glBindVertexArray(this->vaoAddress);
}

void MeshBB::initVbos()
{
	// Generates and makes active the VBO for the vertices
	glGenBuffers(1, &this->verticesVboAddress);
	glBindBuffer(GL_ARRAY_BUFFER, this->verticesVboAddress);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(fvec3), this->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	// Generates and makes active the VBO for the colors
	glGenBuffers(1, &this->colorsVboAddress);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorsVboAddress);
	glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(fvec4), this->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);
}

void MeshBB::initUniformReferences()
{
	this->projectionMatrixUniformLocation = glGetUniformLocation(this->programId, "projectionMatrix");
	this->modelMatrixUniformLocation = glGetUniformLocation(this->programId, "modelMatrix");

	this->currentTimeUniformLocation = glGetUniformLocation(this->programId, "currentTime");
	this->screenSizeUniformLocation = glGetUniformLocation(this->programId, "windowSize");
}

void MeshBB::initBoundingBox()
{
	int n = static_cast<int>(this->vertices.size());
	float minx = this->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
	float miny = this->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

	float maxx = this->vertices[0].x; // Assumiamo che il primo elemento sia il massimo iniziale
	float maxy = this->vertices[0].y; // Assumiamo che il primo elemento sia il massimo iniziale

	for (int i = 1; i < n; i++)
	{
		if (this->vertices[i].x < minx)
		{
			minx = this->vertices[i].x;
		}
		if (this->vertices[i].x > maxx)
		{
			maxx = this->vertices[i].x;
		}

		if (this->vertices[i].y < miny)
		{
			miny = this->vertices[i].y;
		}

		if (this->vertices[i].y > maxy)
		{
			maxy = this->vertices[i].y;
		}
	}

	this->boundingBoxMinObject = fvec4(minx, miny, 0.0, 1.0);
	this->boundingBoxMaxObject = fvec4(maxx, maxy, 0.0, 1.0);

	// Add bounding box vertices to the vertices vector
	this->vertices.push_back(fvec3(this->boundingBoxMinObject.x, this->boundingBoxMinObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	this->vertices.push_back(fvec3(this->boundingBoxMaxObject.x, this->boundingBoxMinObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	this->vertices.push_back(fvec3(this->boundingBoxMaxObject.x, this->boundingBoxMaxObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
	this->vertices.push_back(fvec3(this->boundingBoxMinObject.x, this->boundingBoxMaxObject.y, 0.0));
	this->colors.push_back(fvec4(1.0, 0.0, 0.0, 1.0));
}

void MeshBB::updateBoundingBoxWorld()
{
	this->boundingBoxMinWorld = this->modelMatrix * this->boundingBoxMinObject;
	this->boundingBoxMaxWorld = this->modelMatrix * this->boundingBoxMaxObject;
}