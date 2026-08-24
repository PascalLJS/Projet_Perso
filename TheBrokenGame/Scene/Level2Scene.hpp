#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../Math/MathUtils.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/AnimatedSprite.hpp"
#include "../UI/Santa.hpp"
#include "../CollisionDetection/HitBox.hpp"
#include "../CollisionDetection/CollisionManager.hpp"
#include "Scene.hpp"
#include <map>

/// @class Level2Scene
/// @brief Représente la scène de jeu Niveau2
class Level2Scene : public Scene {
private:
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	CollisionManager collisionManager;
	HitBox *santaHitBox;
	bool debug = true; //< Put it to True for Debug
	
public:
	/// @brief Charge la scène
	void load() {
		SDL_Color lineColor = engine.assetManager.getAsset<Color *>("WhitePure")->getSDLColor();
		Engine::getInstance().resetSizeWindow(Vector2i(1280,720));
		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

		santaHitBox = new HitBox(SANTA_OUT_OF_MAP);
		visualComponents["1Map"] = new Image(Vector2i(0,0), Vector2i(Engine::getInstance().getWidth(), Engine::getInstance().getHeight()),Engine::getInstance().assetManager.getAsset<Texture*>("Map"));
		visualComponents["2Santa"] = new Santa(Engine::getInstance().assetManager.getAsset<Texture*>("Santa"), Vector2f(0.0,0.0), Vector2i(96,96), santaHitBox);
	}

	/// @brief Décharge la scène
	void unload() {
		for (auto it : visualComponents)
			delete it.second;
		visualComponents.clear();
	}

	/// @brief Gère le rendu de la scène
	void handleRender() {
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto it : visualComponents)
			it.second->render();
		//santaHitBox->render();
		Engine::getInstance().swapWindow();
	}

	/// @brief Gère les événements de la scène
	void handleEvent() {
		switch (Event::getType()) {
			case SDL_KEYDOWN:
				switch (Event::getKeyCode()){
					case SDLK_ESCAPE:
						Event::push(SDL_QUIT, false);
						break;
					default:
						break;
				}
				break;
			case SDL_USEREVENT:
				switch (Event::getUserEventCode()) {
					case SANTA_OUT_OF_BOUND:
						dynamic_cast<Santa*>(visualComponents["2Santa"])->repositionSanta();
							break;
					case SANTA_OUT_OF_MAP:
						dynamic_cast<Santa*>(visualComponents["2Santa"])->repositionSantaInsideMap();
							break;
					case SANTA_COLIDED_WITH_PRESENT:
						dynamic_cast<Santa*>(visualComponents["2Santa"])->resetPosition();
							break;
				}
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		dynamic_cast<AnimatedSprite*>(visualComponents["2Santa"])->update(deltaTime);
	}
};