#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../UI/Button.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/Image.hpp"
#include "../UI/LabelGrid.hpp"
#include "../UI/Label.hpp"
#include "GameScene.hpp"
#include "Scene.hpp"
#include "../UI/DialogManager.hpp"
#include <map>

/// @class MainMenu
/// @brief Représente la scène du menu principal
class MainMenu : public Scene {
private:
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	DialogManager *dialogManager;
	
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

		//First Dialog
		LabelGrid *firstDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *dialog0 = new Label(Vector2i(0,0), font24, "Hello and Welcome to The Broken Christmas, a game developed by", dialogText);
		Label *dialog01 = new Label(Vector2i(0,0), font24, "a small team of Santa's elves.", dialogText);
		firstDialog->addLabel(dialog0);
		firstDialog->addLabel(dialog01);

		//Second Dialog
		LabelGrid *secondDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *dialog1 = new Label(Vector2i(0,0), font24, "Unfortunately, something went terribly wrong...", dialogText);
		secondDialog->addLabel(dialog1);
		
		//Third Dialog
		LabelGrid *thirdDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *dialog2 = new Label(Vector2i(0,0), font24, "Your first task is to access the game. Good luck !!", dialogText);
		thirdDialog->addLabel(dialog2);

		visualComponents["0BackGround"] = new Image(Vector2i(0,0), Vector2i(engine.getWidth(), engine.getHeight()), engine.assetManager.getAsset<Texture*>("MenuBackGround"));
		visualComponents["1DialogBox"] = new Image(Vector2i(MathUtils::getCenteredPositionX(engine.getWidth(), 800), 25), Vector2i(800, 150), engine.assetManager.getAsset<Texture*>("Dialog"));
		visualComponents["2firstDialog"] = firstDialog;
		visualComponents["2secondDialog"] = secondDialog;
		visualComponents["2thirdDialog"] = thirdDialog;

		firstDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["1DialogBox"]->getSize(), firstDialog->getSize()) + visualComponents["1DialogBox"]->getPos());
		firstDialog->resetPosition();

		secondDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["1DialogBox"]->getSize(), secondDialog->getSize()) + visualComponents["1DialogBox"]->getPos());
		secondDialog->resetPosition();

		thirdDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["1DialogBox"]->getSize(), thirdDialog->getSize()) + visualComponents["1DialogBox"]->getPos());
		thirdDialog->resetPosition();

		eventManager.subscribe(SDL_MOUSEMOTION, (Button*)visualComponents["100playButton"]);
		
		eventManager.subscribe(SDL_MOUSEBUTTONDOWN, (Button*)visualComponents["100playButton"]);


		dialogManager = new DialogManager(3, ((Image*)visualComponents["1DialogBox"]));
		dialogManager->addDialog(firstDialog);
		dialogManager->addDialog(secondDialog);
		dialogManager->addDialog(thirdDialog);
		dialogManager->activateDialog();
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
						if(!engine.isAllowToPass()) {
							engine.sceneManager.addScene("GameScene", new GameScene());
							engine.sceneManager.transitScene("GameScene");
							break;
						}
						visualComponents["100playButton"]->setPosition(Vector2i(rand() % engine.getWidth() - visualComponents["100playButton"]->getSize().x, rand() % engine.getHeight() - visualComponents["100playButton"]->getSize().y));
						((Button*)visualComponents["100playButton"])->updateLabelPosition();
					break;
				}
				break;
			case SDL_KEYDOWN:
					switch (Event::getKeyCode()) {
						case SDLK_ESCAPE:
							Event::push(SDL_QUIT, false);
							break;
						default:
							if(dialogManager->isDialogActive())
								dialogManager->changeDialog();
						break;
					}
			break;
			default:
				if(dialogManager->isDialogActive()) {
					SDL_SetRelativeMouseMode(SDL_TRUE);
					((Button*)visualComponents["100playButton"])->disableButton();
					dialogManager->setCurrentVisible();
				} else {
					SDL_SetRelativeMouseMode(SDL_FALSE);
					((Button*)visualComponents["100playButton"])->enableButton();
				}
				eventManager.notify(Event::getType());
			break;
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		
	}
};