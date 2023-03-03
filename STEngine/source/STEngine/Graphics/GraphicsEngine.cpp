#include"STEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "STEngine/Graphics/VertexArrayObject.h"
#include "STEngine/CoreMinimal.h"

using namespace std;

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	
	//this will handle deleting the SDL window from memory
	SDL_DestroyWindow(SdlWindow);

	//destroy the GL context for SDL
	SDL_GL_DeleteContext(SdlGLContext);

	//close the SDL framework
	SDL_Quit();

	cout << "Destroy Graphics Engine.." << endl;
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{
	//make sure SDL initializes
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL failed: " << SDL_GetError() << endl;
		return false;
	}

	//Use OpenGL 3.1 and set default attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);

	//Set the fullscreen flag
	int fullScreenFlag = 0;
	if (bFullScreen) {
		fullScreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}

	else {
		fullScreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}
	//create the SDL2 window
	SdlWindow = SDL_CreateWindow(
		WTitle, //title of the window
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //location of the window
		WWidth, WHeight, //width and height of the window
		fullScreenFlag
	);

	if (SdlWindow == nullptr) {
		cout << "SDL window failed: " << SDL_GetError() << endl;
		return false;
	}

	//add all the GL attributes to the window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);

	if (SdlGLContext == NULL) {
		cout << "SDL GL Context failed : " << SDL_GetError() << endl;
		return false;
	}

	//To make glwe work we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK) {
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;

		return false;
	}

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	//present the new graphics using OpenGL
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//set the background colour
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();
	HandleWireframeMode(false);

	//TODO: Add anything that renders between these two functions

	for (VAOPtr VAO : VAOs) {
		VAO->Draw();
	}
	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

void GraphicsEngine::CreateVAO()
{
	//Create a new VAO as a shared pointer
	VAOPtr NewVAO = make_shared<VAO>(GeometricShapes::MyShape);

	//Add it to the stack
	VAOs.push_back(NewVAO);
}

void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	//if wireframe mode is set change it, visa versa
	if (bShowWireframeMode != bWireframeMode) {
		bWireframeMode = bShowWireframeMode;
		//change how openGL renders between the vertices
		if (bWireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		cout << "Wireframe Mode updated.." << endl;
	}
}
