#pragma once
#include "STEngine/CoreMinimal.h"

const PositionMatrix TrianglePositions{
	// X     Y     Z
	-0.5f, -0.5f, 0.0f, //bottom left
	 0.5f, -0.5f, 0.0f,	// bottom right
	 0.0f,  0.5f, 0.0f	//top 

};

const IndicesMatrix TriangleIndices{
	0, 1, 2

};

const PositionMatrix PolyPositions{
	// X     Y     Z
	-0.5f, -0.5f, 0.0f, //bottom left
	 0.5f, -0.5f, 0.0f,	// bottom right
	 0.5f,  0.5f, 0.0f,	//top right 
	 -0.5f,  0.5f, 0.0f	//top left 
};

const IndicesMatrix PolyIndices{
	0, 3, 2, //triangle 1
	0, 2, 1	//triangle 2
};


const PositionMatrix MyShapePositions{
	// X     Y     Z
	0.0f, 0.5f, 0.0f, 
	 0.1f, 0.9f, 0.0f,	
	 0.2f, 0.3f, 0.0f,
	 0.0f, 0.0f, 0.0f,	
	
};

const IndicesMatrix MyShapeIndices{
	0, 1, 3,		//triangle 1
	0, 2, 3		//triangle 2
};


class VertexArrayObject {
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	~VertexArrayObject();

	void Draw();

private:
	ShapeData Shape;
	//this is our version of unsigned int
	//ID - id for VAO
	//VAB -  ID for the vertices
	//EAB - ID for the Indices
	stuint ID, VAB, EAB;
};