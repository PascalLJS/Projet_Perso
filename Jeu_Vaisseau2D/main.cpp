#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

#include "Engine/Engine.hpp"
#include "Scene/Level1Scene.hpp"
#include "Scene/Level2Scene.hpp"
#include "Scene/FlagLevel1Scene.hpp"
#include "Scene/FlagLevel2Scene.hpp"
#include "Assets/Style.hpp"

int main(int argc, char *argv[]) { 
	Engine &engine = Engine::getInstance();
	Style style{engine.assetManager};

	engine.sceneManager.addScene("Level1Scene", new Level1Scene());
	engine.sceneManager.addScene("Level2Scene", new Level2Scene());
	engine.sceneManager.addScene("FlagLevel1Scene", new FlagLevel1Scene());
	engine.sceneManager.addScene("FlagLevel2Scene", new FlagLevel2Scene());
	engine.sceneManager.transitScene("Level1Scene");

	engine.start();

	return 0;
}