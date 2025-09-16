#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

#include "Engine/Engine.hpp"
#include "Scene/MainMenuScene.hpp"
#include "Scene/GameScene.hpp"
#include "Assets/Style.hpp"

int main(int argc, char *argv[]) { 
	Engine &engine = Engine::getInstance();
	Style style{engine.assetManager};

	engine.sceneManager.addScene("MainMenuScene", new MainMenuScene());
	engine.sceneManager.addScene("GameScene", new GameScene());
	engine.sceneManager.transitScene("MainMenuScene");

	engine.start();

	return 0;
}