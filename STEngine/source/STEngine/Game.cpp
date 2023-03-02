#include "STEngine/Game.h"

Game::Game()
{
	cout << "Game Initialized!" << endl;
	
	bIsGameOver = false;
	Graphics = nullptr;
}

Game::~Game()
{
	//since nothing else is storing is graphics memory 
	//this will destroy the  graphics from memory
	Graphics = nullptr;
	
	cout << "Game Over.." << endl;
}

void Game::Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{

	Graphics = make_shared<GraphicsEngine>();

	if (!Graphics->InitGE(WTitle, bFullScreen, WWidth, WHeight)) {
		bIsGameOver = true;
	}


	Run();
}



void Game::Run()
{
	if (!bIsGameOver) {
		//Create a triangle
		Graphics->CreateVAO();
	}
	//as long as the game is not over
	while (!bIsGameOver) {
		//make sure we process what the user has done
		ProcessInput();

		//apply the logic base on the inputs and the game logic
		Update();

		//render the screen based on the function above
		Draw();
	}

	//clean the game after it ends
	CloseGame();
}

void Game::ProcessInput()
{
	//TODO: Handle input
	SDL_Event PollEvent;
	//this is waiting for inputs to be pressed
	while (SDL_PollEvent(&PollEvent)) {
		switch (PollEvent.type) {
		case SDL_QUIT:
			bIsGameOver = true;
			break;

		default:
			break;
		}
	}
}

void Game::Update()
{
	//TODO: handle logic
}

void Game::Draw()
{
	//todo handle the graphics

	Graphics->Draw();

}

void Game::CloseGame()
{
	//todo handle the run
}

Game& Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return *GameInstance;
	// TODO: insert return statement here
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();

	delete GameInstance;
}

