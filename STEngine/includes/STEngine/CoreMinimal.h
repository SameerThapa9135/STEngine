#pragma once
#include <iostream>
#include <vector>


using namespace std;

typedef unsigned int stuint;

//class/ type definitions 
class GraphicsEngine;

typedef shared_ptr<GraphicsEngine> GEPtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;
typedef vector<VAOPtr> VAOStack;

//useful for shape data and VAOs Matrices 
typedef vector<float> PositionMatrix;
typedef vector<stuint> IndicesMatrix;


// this structure handles matrices for VAO
struct ShapeData {
	vector<float> PositionMatrix;
	vector<stuint> IndicesMatrix;
};