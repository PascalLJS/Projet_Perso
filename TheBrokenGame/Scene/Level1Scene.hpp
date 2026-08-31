#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../UI/Button.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/Image.hpp"
#include "Scene.hpp"
#include <map>

/// @class Level1Scene
/// @brief Représente la scène du menu principal
class Level1Scene : public Scene {
private:
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	bool dialogActive = true;
	
public:
	/// @brief Charge la scène
	void load() {
		Font* font24 = engine.assetManager.getAsset<Font*>("fontBold24");
		Font* font32 = engine.assetManager.getAsset<Font*>("fontBold32");
		SDL_Color dialogText = engine.assetManager.getAsset<Color *>("BlackPure")->getSDLColor();
		SDL_Color menuButtonColor = engine.assetManager.getAsset<Color *>("GrayDark1")->getSDLColor();
		SDL_Color menuButtonHoverColor = engine.assetManager.getAsset<Color *>("GrayLight2")->getSDLColor();
		Vector2i menuButtonSize = Vector2i(125, 50);

		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

		visualComponents["100playButton"] = new Button("Play",
			font32,
			engine.assetManager.getAsset<Color*>("WhitePure")->getSDLColor(),
			MathUtils::getCenteredPosition(engine.getSize(), menuButtonSize),
			menuButtonSize,
			menuButtonColor,
			menuButtonHoverColor,
			PLAY_BUTTON_CLICK
		);

		visualComponents["0BackGround"] = new Image(Vector2i(0,0), Vector2i(engine.getWidth(), engine.getHeight()), engine.assetManager.getAsset<Texture*>("MenuBackGround"));
		visualComponents["1Dialog"] = new Image(Vector2i(MathUtils::getCenteredPositionX(engine.getWidth(), 800), 25), Vector2i(800, 150), engine.assetManager.getAsset<Texture*>("Dialog"));
		visualComponents["2DialogText"] = new Label(Vector2i(0,0), font24, "Bonjour, test", dialogText);
		visualComponents["2DialogText"]->setPosition(MathUtils::getCenteredPosition(visualComponents["1Dialog"]->getSize(), visualComponents["2DialogText"]->getSize()) + visualComponents["1Dialog"]->getPos());

		eventManager.subscribe(SDL_MOUSEMOTION, (Button*)visualComponents["100playButton"]);
		eventManager.subscribe(SDL_MOUSEBUTTONDOWN, (Button*)visualComponents["100playButton"]);
	}

	/// @brief Décharge la scène
	void unload() {
		eventManager.unsubscribe(SDL_MOUSEMOTION, (Button*)visualComponents["100playButton"]);
		eventManager.unsubscribe(SDL_MOUSEBUTTONDOWN, (Button*)visualComponents["100playButton"]);

		for (auto it : visualComponents)
			delete it.second;
		visualComponents.clear();
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
		switch (Event::getType()) {
			case SDL_USEREVENT:
				switch (Event::getUserEventCode()) {
					case PLAY_BUTTON_CLICK:
						if(engine.isAllowToPass()) {
							visualComponents["100playButton"]->setPosition(Vector2i(rand() % engine.getWidth() - visualComponents["100playButton"]->getSize().x, rand() % engine.getHeight() - visualComponents["100playButton"]->getSize().y));
							((Button*)visualComponents["100playButton"])->updateLabelPosition();
							break;
						}
						engine.sceneManager.transitScene("FlagLevel1Scene");
					break;
				}
				break;
			case SDL_KEYDOWN:
					switch (Event::getKeyCode()) {
						case SDLK_ESCAPE:
							Event::push(SDL_QUIT, false);
							break;
						case SDLK_RETURN:
							delete visualComponents["1Dialog"];
							visualComponents.erase("1Dialog");
							break;
					}
			break;
			default:
				eventManager.notify(Event::getType());
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		
	}
};