#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../Math/MathUtils.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/AnimatedSprite.hpp"
#include "Scene.hpp"
#include <map>

/// @class Level2Scene
/// @brief Représente la scène de jeu
class Level2Scene : public Scene {
private:
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	
public:
	/// @brief Charge la scène
	void load() {
		Engine::getInstance().resetSizeWindow(Vector2i(1280,720));
		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

		visualComponents["1Map"] = new Image(Vector2i(0,0), Vector2i(Engine::getInstance().getWidth(), Engine::getInstance().getHeight()),Engine::getInstance().assetManager.getAsset<Texture*>("Map"));
		visualComponents["2Santa"] = new AnimatedSprite(Engine::getInstance().assetManager.getAsset<Texture*>("Santa"), Vector2i(0,0), Vector2i(64,64));

	}

	/// @brief Décharge la scène
	void unload() {
		
	}

	/// @brief Gère le rendu de la scène
	void handleRender() {
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto it : visualComponents)
			it.second->render();
		Engine::getInstance().swapWindow();
	}

	/// @brief Gère les événements de la scène
	void handleEvent() {
		SDL_Event currentEvent;
		currentEvent.type = Event::getType();

		switch (Event::getType()) {
			case SDL_MOUSEMOTION:
				
				break;
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		
	}
	
};