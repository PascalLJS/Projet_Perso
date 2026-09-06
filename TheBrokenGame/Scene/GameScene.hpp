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
#include "../UI/Image.hpp"
#include "../UI/LabelGrid.hpp"
#include "../UI/Label.hpp"
#include "../UI/DeathRock.hpp"
#include "FlagScene.hpp"
#include "../CollisionDetection/HitBox.hpp"
#include "../CollisionDetection/CollisionManager.hpp"
#include "Scene.hpp"
#include "../UI/DialogManager.hpp"
#include <map>

/// @class GameScene
/// @brief Représente la scène de jeu
class GameScene : public Scene {
private:
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	std::map<string, AnimatedSprite*> animatedSprites;
	std::map<string, HitBox*> hitboxes;
	DeathRock *deathRock;
	DialogManager *dialogManager;
	CollisionManager collisionManager;
	bool debug = false; //< Put it to True for Debug
	bool inAnimation = false;
	
public:
	/// @brief Charge la scène
	void load() {
		SDL_Color lineColor = engine.assetManager.getAsset<Color *>("WhitePure")->getSDLColor();
		SDL_Color dialogText = engine.assetManager.getAsset<Color *>("BlackPure")->getSDLColor();
		Font* font24 = engine.assetManager.getAsset<Font*>("fontBold24");
		Engine::getInstance().resetSizeWindow(Vector2i(1280,720));
		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

		hitboxes["1santaHitBox"] = new HitBox(SANTA_OUT_OF_MAP);
		hitboxes["2HitBoxPresent0"] = new HitBox(SANTA_COLIDED_WITH_PRESENT);
		hitboxes["2HitBoxPresent1"] = new HitBox(SANTA_COLIDED_WITH_PRESENT);
		hitboxes["2deathRockHitbox"] = new HitBox(SANTA_DEAD);
		hitboxes["2wall0"] = new HitBox(Vector2f(0.0, 105), Vector2i(295, 10), SANTA_OUT_OF_BOUND);
		hitboxes["2wall1"] = new HitBox(Vector2f(540, 0.0), Vector2i(300, 350), SANTA_OUT_OF_BOUND);
		hitboxes["2wall2"] = new HitBox(Vector2f(0.0, 530), Vector2i(60, 280), SANTA_OUT_OF_BOUND);
		hitboxes["2wall3"] = new HitBox(Vector2f(380, 350), Vector2i(500, 75), SANTA_OUT_OF_BOUND);
		hitboxes["2wall4"] = new HitBox(Vector2f(400, 425), Vector2i(480, 85), SANTA_OUT_OF_BOUND);
		hitboxes["2wall5"] = new HitBox(Vector2f(480, 510), Vector2i(400, 25), SANTA_OUT_OF_BOUND);
		hitboxes["2wall6"] = new HitBox(Vector2f(550, 535), Vector2i(330, 15), SANTA_OUT_OF_BOUND);
		hitboxes["2wall7"] = new HitBox(Vector2f(840, 0.0), Vector2i(440, 110), SANTA_OUT_OF_BOUND);
		hitboxes["2wall8"] = new HitBox(Vector2f(1180, 110), Vector2i(100, 670), SANTA_OUT_OF_BOUND);
		hitboxes["2deathWall"] = new HitBox(Vector2f(880, 350), Vector2i(300, 20), SANTA_DEATH_ANIMATION);
		hitboxes["2homeCarpet"] = new HitBox(Vector2f(975, 100), Vector2i(75, 25), SANTA_HOME);

		visualComponents["1Map"] = new Image(Vector2i(0,0), Vector2i(engine.getWidth(), engine.getHeight()), engine.assetManager.getAsset<Texture*>("Map"));
		visualComponents["2DialogBox"] = new Image(Vector2i(MathUtils::getCenteredPositionX(engine.getWidth(), 800), 25), Vector2i(800, 150), engine.assetManager.getAsset<Texture*>("Dialog"));
		visualComponents["2deadSanta"] = new Image(Vector2i(-300,-300), Vector2i(256, 256), engine.assetManager.getAsset<Texture*>("DeadSanta"));
		animatedSprites["2Santa"] = new Santa(engine.assetManager.getAsset<Texture*>("Santa"), Vector2f(0.0,0.0), Vector2i(96,96), hitboxes["1santaHitBox"]);
		animatedSprites["3Present0"] = new Present(engine.assetManager.getAsset<Texture*>("Present"), Vector2f(30, 550), Vector2i(64,64), 1, 720, hitboxes["2HitBoxPresent0"]);
		animatedSprites["3Present1"] = new Present(engine.assetManager.getAsset<Texture*>("Present"), Vector2f(1135, 630), Vector2i(64,64), 2, 720, hitboxes["2HitBoxPresent1"]);
		deathRock = new DeathRock(
														Vector2f(0.0, 0.0),
														Vector2i(128,128),
														engine.assetManager.getAsset<Texture*>("Rock"),
														hitboxes["2deathRockHitbox"]
													);

		dialogManager = new DialogManager(3, ((Image*)visualComponents["2DialogBox"]));
		///FirstDialog
		LabelGrid *firstDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *label0 = new Label(Vector2i(0,0), font24, "You made it !! I knew you could do it, but your task is not over yet,", dialogText);
		Label *label1 = new Label(Vector2i(0,0), font24, "I still need you to help Santa get into is home...", dialogText);
		firstDialog->addLabel(label0);
		firstDialog->addLabel(label1);

		//Second Dialog
		LabelGrid *secondDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *label2 = new Label(Vector2i(0,0), font24, "Some will say it is an impossible task, but I know for sure it is !!", dialogText);
		secondDialog->addLabel(label2);

		///Third Dialog
		LabelGrid *thirdDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *label3 = new Label(Vector2i(0,0), font24, "I would like to see you give it a try before doing anything else.", dialogText);
		thirdDialog->addLabel(label3);

		//DeathDialog
		LabelGrid *deathDialogG0 = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *deathdialog0 = new Label(Vector2i(0,0), font24, "Oops !! I do not know who put that here...", dialogText);
		deathDialogG0->addLabel(deathdialog0);

		//DeathDialog
		LabelGrid *deathDialogG1 = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *deathdialog1 = new Label(Vector2i(0,0), font24, "Well I guess it was an impossible task..", dialogText);
		deathDialogG1->addLabel(deathdialog1);

		//DeathDialog
		LabelGrid *deathDialogG2 = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
		Label *deathdialog2 = new Label(Vector2i(0,0), font24, "At least you have access to the game files so you can work", dialogText);
		Label *deathdialog3 = new Label(Vector2i(0,0), font24, "your way around it !! I believe in you :)", dialogText);
		deathDialogG2->addLabel(deathdialog2);
		deathDialogG2->addLabel(deathdialog3);

		dialogManager->addDialog(firstDialog);
		dialogManager->addDialog(secondDialog);
		dialogManager->addDialog(thirdDialog);
		dialogManager->addDialog(deathDialogG0);
		dialogManager->addDialog(deathDialogG1);
		dialogManager->addDialog(deathDialogG2);

		visualComponents["3firstDialog"] = firstDialog;
		visualComponents["3secondDialog"] = secondDialog;
		visualComponents["3thirdDialog"] = thirdDialog;
		visualComponents["4deathDialog0"] = deathDialogG0;
		visualComponents["4deathDialog1"] = deathDialogG1;
		visualComponents["4deathDialog2"] = deathDialogG2;

		firstDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["2DialogBox"]->getSize(), firstDialog->getSize()) + visualComponents["2DialogBox"]->getPos());
		firstDialog->resetPosition();

		secondDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["2DialogBox"]->getSize(), secondDialog->getSize()) + visualComponents["2DialogBox"]->getPos());
		secondDialog->resetPosition();

		thirdDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["2DialogBox"]->getSize(), thirdDialog->getSize()) + visualComponents["2DialogBox"]->getPos());
		thirdDialog->resetPosition();

		deathDialogG0->setPosition(MathUtils::getCenteredPosition(visualComponents["2DialogBox"]->getSize(), deathDialogG0->getSize()) + visualComponents["2DialogBox"]->getPos());
		deathDialogG0->resetPosition();

		deathDialogG1->setPosition(MathUtils::getCenteredPosition(visualComponents["2DialogBox"]->getSize(), deathDialogG1->getSize()) + visualComponents["2DialogBox"]->getPos());
		deathDialogG1->resetPosition();

		deathDialogG2->setPosition(MathUtils::getCenteredPosition(visualComponents["2DialogBox"]->getSize(), deathDialogG2->getSize()) + visualComponents["2DialogBox"]->getPos());
		deathDialogG2->resetPosition();

		dialogManager->activateDialog();
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

		delete dialogManager;
		delete deathRock;
	}

	/// @brief Gère le rendu de la scène
	void handleRender() {
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto it : visualComponents)
			it.second->render();

		for (auto it : animatedSprites)
			it.second->render();

		if(isInAnimation())
			deathRock->render();

		if(debug)
			for (auto it : hitboxes)
				it.second->render();

		Engine::getInstance().swapWindow();
	}

	bool isInAnimation() {
		return inAnimation;
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
						if(dialogManager->isDialogActive())
							dialogManager->changeDialog();
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
					case SANTA_DEATH_ANIMATION:
						inAnimation = true;
						animatedSprites["2Santa"]->resetAnimation(); 
						animatedSprites["2Santa"]->resetDirection();
						deathRock->setPosition(hitboxes["1santaHitBox"]->getPos());
						break;
					case SANTA_DEAD:
						inAnimation = false;
						deathRock->setPosition(Vector2f(1280, 0)); deathRock->updateHitbox();
						visualComponents["2deadSanta"]->setPosition(Vector2i(hitboxes["1santaHitBox"]->getPos().x - 75, hitboxes["1santaHitBox"]->getPos().y - 30));
						if(!((Image*)visualComponents["2deadSanta"])->isVisible())
							((Image*)visualComponents["2deadSanta"])->setVisible();
						animatedSprites["2Santa"]->resetPosition();
						animatedSprites["2Santa"]->setInvisible();
						if(!dialogManager->noMoreDialog()) {
							dialogManager->resetCounter(3);
							dialogManager->activateDialog();
						}
						break;
					case SANTA_HOME:
						engine.sceneManager.addScene("FlagScene", new FlagScene());
						engine.sceneManager.transitScene("FlagScene");
						break;
				}
			default:
				if(dialogManager->isDialogActive()) {
					SDL_SetRelativeMouseMode(SDL_TRUE);
				} else {
					SDL_SetRelativeMouseMode(SDL_FALSE);
				}
				if(dialogManager->noMoreDialog()) {
					((Image*)visualComponents["2deadSanta"])->setInvisible();
					animatedSprites["2Santa"]->setVisible();
				}
			break;
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		if(!isInAnimation() && !dialogManager->isDialogActive()) {
			bool isCollisionWithObstacles = false;

			if(!collisionManager.checkOutOfMap(hitboxes["1santaHitBox"], engine.getSize(), animatedSprites["2Santa"]->getDirection())) {
				for(auto it = ++hitboxes.begin(); it != hitboxes.end(); ++it)
					if(collisionManager.checkCollision(hitboxes["1santaHitBox"], it->second, animatedSprites["2Santa"]->getDirection()))
						isCollisionWithObstacles = true;
				
				if(!isCollisionWithObstacles)
					animatedSprites["2Santa"]->update(deltaTime);

				for(auto it = ++animatedSprites.begin(); it != animatedSprites.end(); ++it)
					it->second->update(deltaTime);
			}
		}
		if(isInAnimation()) {
			deathRock->update(deltaTime);
			collisionManager.checkCollision(hitboxes["1santaHitBox"], hitboxes["2deathRockHitbox"], 0.0);
		}
	}
};