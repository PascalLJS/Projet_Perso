#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../Math/MathUtils.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/AnimatedSprite.hpp"
#include "../UI/Santa.hpp"
#include "../UI/Present.hpp"
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
	std::map<string, AnimatedSprite*> animatedSprites;
	std::map<string, HitBox*> hitboxes;
	CollisionManager collisionManager;
	bool debug = false; //< Put it to True for Debug
	
public:
	/// @brief Charge la scène
	void load() {
		SDL_Color lineColor = engine.assetManager.getAsset<Color *>("WhitePure")->getSDLColor();
		Engine::getInstance().resetSizeWindow(Vector2i(1280,720));
		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

		hitboxes["1santaHitBox"] = new HitBox(SANTA_OUT_OF_MAP);
		hitboxes["2HitBoxPresent0"] = new HitBox(SANTA_COLIDED_WITH_PRESENT);
		hitboxes["2HitBoxPresent1"] = new HitBox(SANTA_COLIDED_WITH_PRESENT);
		hitboxes["2wall0"] = new HitBox(Vector2f(0.0, 105), Vector2i(295, 10), SANTA_OUT_OF_BOUND);
		hitboxes["2wall1"] = new HitBox(Vector2f(540, 0.0), Vector2i(300, 350), SANTA_OUT_OF_BOUND);
		hitboxes["2wall2"] = new HitBox(Vector2f(0.0, 530), Vector2i(60, 280), SANTA_OUT_OF_BOUND);
		hitboxes["2wall3"] = new HitBox(Vector2f(380, 350), Vector2i(500, 75), SANTA_OUT_OF_BOUND);
		hitboxes["2wall4"] = new HitBox(Vector2f(400, 425), Vector2i(480, 85), SANTA_OUT_OF_BOUND);
		hitboxes["2wall5"] = new HitBox(Vector2f(480, 510), Vector2i(400, 25), SANTA_OUT_OF_BOUND);
		hitboxes["2wall6"] = new HitBox(Vector2f(550, 535), Vector2i(330, 15), SANTA_OUT_OF_BOUND);
		hitboxes["2wall7"] = new HitBox(Vector2f(840, 0.0), Vector2i(440, 110), SANTA_OUT_OF_BOUND);
		hitboxes["2wall8"] = new HitBox(Vector2f(1180, 110), Vector2i(100, 670), SANTA_OUT_OF_BOUND);

		visualComponents["1Map"] = new Image(Vector2i(0,0), Vector2i(Engine::getInstance().getWidth(), Engine::getInstance().getHeight()),Engine::getInstance().assetManager.getAsset<Texture*>("Map"));
		animatedSprites["2Santa"] = new Santa(Engine::getInstance().assetManager.getAsset<Texture*>("Santa"), Vector2f(0.0,0.0), Vector2i(96,96), hitboxes["1santaHitBox"]);
		animatedSprites["3Present0"] = new Present(Engine::getInstance().assetManager.getAsset<Texture*>("Present"), Vector2f(30, 550), Vector2i(64,64), 1, 720, hitboxes["2HitBoxPresent0"]);
		animatedSprites["3Present1"] = new Present(Engine::getInstance().assetManager.getAsset<Texture*>("Present"), Vector2f(1135, 630), Vector2i(64,64), 2, 720, hitboxes["2HitBoxPresent1"]);
	}

	/// @brief Décharge la scène
	void unload() {
		for (auto it : visualComponents)
			delete it.second;
		visualComponents.clear();
		for (auto it : animatedSprites)
			delete it.second;
		animatedSprites.clear();
		for (auto it : hitboxes)
			delete it.second;
		hitboxes.clear();
	}

	/// @brief Gère le rendu de la scène
	void handleRender() {
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto it : visualComponents)
			it.second->render();

		for (auto it : animatedSprites)
			it.second->render();

		if(debug)
			for (auto it : hitboxes)
				it.second->render();
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
				}
				break;
			case SDL_USEREVENT:
				switch (Event::getUserEventCode()) {
					case SANTA_OUT_OF_BOUND:
					case SANTA_OUT_OF_MAP:
						animatedSprites["2Santa"]->reposition(collisionManager.getPenetration());
							break;
					case SANTA_COLIDED_WITH_PRESENT:
						animatedSprites["2Santa"]->resetPosition();
							break;
				}
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		bool isCollisionWithObstacles = false;

		if(!collisionManager.checkOutOfMap(hitboxes["1santaHitBox"], Engine::getInstance().getSize(), animatedSprites["2Santa"]->getDirection())) {
			for(auto it = ++hitboxes.begin(); it != hitboxes.end(); ++it)
				if(collisionManager.checkCollision(hitboxes["1santaHitBox"], it->second, animatedSprites["2Santa"]->getDirection()))
					isCollisionWithObstacles = true;
			
			if(!isCollisionWithObstacles)
				animatedSprites["2Santa"]->update(deltaTime);

			for(auto it = ++animatedSprites.begin(); it != animatedSprites.end(); ++it)
				it->second->update(deltaTime);
		}
	}
};