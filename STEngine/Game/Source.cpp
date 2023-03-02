#include "STEngine/Game.h"

int main(int argc, char** argv) {


	Game::GetGameInstance().Start("STEngine | AN OpenGL Engine", false, 960, 720);

	Game::DestroyGameInstance();

	return 0;
}