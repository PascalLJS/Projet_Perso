#include "SDL2/SDL_main.h"

#include "Engine/Engine.hpp"
#include "Scene/MainMenuScene.hpp"
#include "Scene/HiddenSecretScene.hpp"
#include "Assets/Style.hpp"

int main(int argc, char *argv[]) {
	Engine &engine = Engine::getInstance();
	Style style{engine.assetManager};

	engine.sceneManager.addScene("HiddenSecretScene", new HiddenSecretScene());
	engine.sceneManager.addScene("MainMenuScene", new MainMenu());
	engine.sceneManager.transitScene("MainMenuScene");

	engine.start();

	return 0;
}