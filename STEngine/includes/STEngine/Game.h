#pragma once

#include "STEngine/Graphics/GraphicsEngine.h"
#include "CoreMinimal.h"

class Game {
private:
	Game();
	~Game();

	void Run(); //run the game loop

	//handle the input 
	void ProcessInput();


	//Handles game logic
	void Update();

	
	//Handle 3D graphics drawing to the screen
	//will clear and present each frame
	void Draw();

	//Handle anything that needs to be deleted when the game ends.
	void CloseGame();
private:
	//boolean that ends the game
	bool bIsGameOver;

	//shared pointer to the graphics
	GEPtr Graphics;


public:
	//get the game instance or create one if it doesn't exist
	static Game& GetGameInstance();

	//Destroy the game running the destructer
	static void DestroyGameInstance();

	//Start the game
	void Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight);
};