#include "STEngine//Graphics/VertexArrayObject.h"
#include "GL/glew.h"


VertexArrayObject::VertexArrayObject(GeometricShapes ChosenShape)
{
	ID = EAB = VAB = 0;

	//Localized version of the chosen matrices
	PositionMatrix ChosenPosition = PositionMatrix();
	IndicesMatrix ChosenIndices = IndicesMatrix();
	
	switch (ChosenShape) {
	case GeometricShapes::Triangle:
		ChosenPosition = TrianglePositions;
		ChosenIndices = TriangleIndices;
		break;

	case GeometricShapes::Polygon:
		ChosenPosition = PolyPositions;
		ChosenIndices = PolyIndices;
		break;

	case GeometricShapes::MyShape:
		ChosenPosition = MyShapePositions;
		ChosenIndices = MyShapeIndices;
		break;

	default:
		break;
	}

	Shape.PositionMatrix = ChosenPosition;
	Shape.IndicesMatrix = ChosenIndices;

	
	// Handle the positions
	
	//create the ID for our VAO
	glGenVertexArrays(1, &ID);

	//bind the data to this vertex array
	glBindVertexArray(ID);

	// create an ID for out array buffer
	glGenBuffers(1, &VAB);

	//bind the above IDs to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);

	//Run through the data and attach the vertices to VAB
	glBufferData(GL_ARRAY_BUFFER,
		Shape.PositionMatrix.size() * sizeof(float),
		&Shape.PositionMatrix[0],
		GL_STATIC_DRAW
	);

	//Handle the indices
	// create an id for our element array buffer
	glGenBuffers(1, &EAB);

	//bind the above ID to openGL as the current buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);

	// Run through the data and attach the indices to the EAB
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		Shape.IndicesMatrix.size() * sizeof(stuint),
		&Shape.IndicesMatrix[0],
		GL_STATIC_DRAW
	);

	//Assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,	//Data Set - 0 = the first data set in the array
		3,	// numbers in our matrix to make a triangle
		GL_FLOAT, GL_FALSE, //data type, whether you want to normalize the value
		sizeof(float) * 3,	//stride - the length it takes to get to each number
		(void*)0	//offset of how many number to skip in the matrix
	);

	//enable the vertex array
	glEnableVertexAttribArray(0);

	//clear the buffer
	glBindVertexArray(0);

}

VertexArrayObject::~VertexArrayObject()
{
	//clean up the VAO in OpenGL
	glDeleteVertexArrays(1, &ID);

	//CLean up the vectors
	Shape.PositionMatrix.clear();

	Shape.IndicesMatrix.clear();
	
	cout << "Deleted VAO....." << endl;
}

void VertexArrayObject::Draw()
{
	// bind our VAO to the current buffer
	glBindVertexArray(ID);

	//Draw the 3D object/ VAO
	glDrawElements(
		GL_TRIANGLES,  //what type of objects are we drawing
		Shape.IndicesMatrix.size(),	// how many vertices do we draw
		GL_UNSIGNED_INT,	// what is the type of data that's being input 
		(void*)0	//how many we should skip
	);

	//clear the VAO from the current array to allow for the next object
	glBindVertexArray(0);
}
