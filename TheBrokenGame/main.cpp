#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

#include "Engine/Engine.hpp"
#include "Scene/MainMenuScene.hpp"
#include "Assets/Style.hpp"

int main(int argc, char *argv[]) {
	Engine &engine = Engine::getInstance();
	Style style{engine.assetManager};

	engine.sceneManager.addScene("MainMenu", new MainMenu());
	engine.sceneManager.transitScene("MainMenu");

	engine.start();

	return 0;
}