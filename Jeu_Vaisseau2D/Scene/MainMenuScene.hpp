#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../UI/Button.hpp"
#include "../Math/Matrix.hpp"
#include "Scene.hpp"
#include <map>

/// @class MainMenuScene
/// @brief Représente la scène du menu principal
class MainMenuScene : public Scene {
private:
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	
public:
	/// @brief Charge la scène
	void load() {
		Font* font = engine.assetManager.getAsset<Font*>("fontBold32");
		SDL_Color menuButtonColor = engine.assetManager.getAsset<Color *>("GrayDark1")->getSDLColor();
		SDL_Color menuButtonHoverColor = engine.assetManager.getAsset<Color *>("GrayLight2")->getSDLColor();
		SDL_Color quitButtonColor = engine.assetManager.getAsset<Color *>("RedDefault")->getSDLColor();
		SDL_Color quitButtonHoverColor = engine.assetManager.getAsset<Color *>("RedLight")->getSDLColor();
		Vector2i menuButtonSize = Vector2i(125, 50);
		Vector2i quitButtonSize = Vector2i(25, 25);

		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

		visualComponents["playButton"] = new Button("Play",
			font,
			engine.assetManager.getAsset<Color*>("WhitePure")->getSDLColor(),
			MathUtils::getCenteredPosition(engine.getWidth(), engine.getHeight(), menuButtonSize.x, menuButtonSize.y),
			menuButtonSize,
			menuButtonColor,
			menuButtonHoverColor,
			PLAY_BUTTON_CLICK
		);
		eventManager.subscribe(SDL_MOUSEMOTION, (Button*)visualComponents["playButton"]);
		eventManager.subscribe(SDL_MOUSEBUTTONDOWN, (Button*)visualComponents["playButton"]);
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
	Engine& engine = Engine::getInstance();
		switch (Event::getType()) {
			case SDL_USEREVENT:
				switch (Event::getUserEventCode()) {
					case PLAY_BUTTON_CLICK:
						engine.sceneManager.transitScene("GameScene");
						break;
					case QUIT_APPLICATION:
						Event::push(SDL_QUIT, false);
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