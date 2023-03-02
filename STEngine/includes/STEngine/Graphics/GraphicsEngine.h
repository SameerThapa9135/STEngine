#pragma once
#include "SDL2/SDL.h"
#include "STEngine/CoreMinimal.h"

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

	//create the windows
	bool InitGE(const char* WTitle, bool bFullScreen, int WWidth, int WHeight);

	//show the newest frame graphics
	void PresentGraphics();

	//clear the old frame graphics
	void ClearGraphics();

	//handle the rendering of the graphics
	void Draw();

	//return the sdl window
	SDL_Window* GetWindow() const;

	//add a new VAO to the VAOStack
	void CreateVAO();

private:
	//this will hold the window
	SDL_Window* SdlWindow;

	// this will allow OpenGL to work in SDL
	SDL_GLContext SdlGLContext;

	// stack all the VAOs
	VAOStack VAOs;

	//handle wireframe mode
	void HandleWireframeMode(bool bShowWireframeMode);

	//set wireframe
	bool bWireframeMode;

};