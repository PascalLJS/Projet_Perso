#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../UI/Button.hpp"
#include "../UI/ButtonGrid.hpp"
#include "../UI/Image.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/LabelGrid.hpp"
#include "../UI/Label.hpp"
#include "../UI/LabelWrapper.hpp"
#include "GameScene.hpp"
#include "Scene.hpp"
#include "../UI/DialogManager.hpp"
#include <map>
#include <string>

/// @class MainMenu
/// @brief Représente la scène du menu principal
class HiddenSecretScene : public Scene {
  private:
    EventManager eventManager;				///< Gestionnaire d'événements
    Engine &engine = Engine::getInstance(); ///< Instance du moteur
    Matrix projection;
    std::map<string, VisualComponent*> visualComponents;
    DialogManager *dialogManager;
    ButtonGrid *buttonGrid;
    std::string enteredCode = "";
    
  public:
    /// @brief Charge la scène
    void load() {
      Font* font24 = engine.assetManager.getAsset<Font*>("fontBold24");
      Font* font32 = engine.assetManager.getAsset<Font*>("fontBold32");
      SDL_Color dialogText = engine.assetManager.getAsset<Color *>("BlackPure")->getSDLColor();
      SDL_Color White = engine.assetManager.getAsset<Color *>("WhitePure")->getSDLColor();
      SDL_Color ButtonColor = engine.assetManager.getAsset<Color *>("GrayDark1")->getSDLColor();
      SDL_Color ButtonHoverColor = engine.assetManager.getAsset<Color *>("GrayLight2")->getSDLColor();
      Vector2i ButtonSize = Vector2i(75, 50);

      projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glMultMatrixf(projection);

      ///FirstDialog
      LabelGrid *firstDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
      Label *label0 = new Label(Vector2i(0,0), font24, "Wow... I honestly didn't expect you to make it this far.", dialogText);
      Label *label1 = new Label(Vector2i(0,0), font24, "But let's see if you're really as clever as you think you are.", dialogText);
      firstDialog->addLabel(label0);
      firstDialog->addLabel(label1);

      //Second Dialog
      LabelGrid *secondDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
      Label *dialog1 = new Label(Vector2i(0,0), font24, "I've sent you a little code.", dialogText);
      Label *dialog12 = new Label(Vector2i(0,0), font24, "Eight digits. Nothing too complicated... right?", dialogText);
      secondDialog->addLabel(dialog1);
      secondDialog->addLabel(dialog12);

      //Third Dialog
      LabelGrid *thirdDialog = new LabelGrid(Vector2i(0,0), Vector2i(0,0), 0);
      Label *dialog2 = new Label(Vector2i(0,0), font24, "Now, prove you got it.", dialogText);
      Label *dialog22 = new Label(Vector2i(0,0), font24, "Can you confirm those eight digits for me?", dialogText);
      thirdDialog->addLabel(dialog2);
      thirdDialog->addLabel(dialog22);

      visualComponents["3Banner"] = new Image(Vector2i(MathUtils::getCenteredPositionX(engine.getWidth(), 800), 25), Vector2i(800, 150), engine.assetManager.getAsset<Texture*>("Dialog"));
      visualComponents["3firstDialog"] = firstDialog;
      visualComponents["3secondDialog"] = secondDialog;
      visualComponents["3thirdDialog"] = thirdDialog;

      firstDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["3Banner"]->getSize(), firstDialog->getSize()) + visualComponents["3Banner"]->getPos());
      firstDialog->resetPosition();

      secondDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["3Banner"]->getSize(), secondDialog->getSize()) + visualComponents["3Banner"]->getPos());
      secondDialog->resetPosition();

      thirdDialog->setPosition(MathUtils::getCenteredPosition(visualComponents["3Banner"]->getSize(), thirdDialog->getSize()) + visualComponents["3Banner"]->getPos());
      thirdDialog->resetPosition();

      buttonGrid = new ButtonGrid(Vector2i(0,0), Vector2i(0,0), 10, 3, 4);

      visualComponents["enteredCode"] = new Label(Vector2i(0,0), font24, "", White);

      visualComponents["labelWrapper"] = new LabelWrapper(Vector2i(MathUtils::getCenteredPositionX(engine.getWidth(), 235), 325), Vector2i(235, 50), White, ((Label*)visualComponents["enteredCode"]), 5);

      visualComponents["1button1"] = new Button("1",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_1
		  );

      visualComponents["1button2"] = new Button("2",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_2
		  );

      visualComponents["1button3"] = new Button("3",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_3
		  );

      visualComponents["1button4"]= new Button("4",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_4
		  );

      visualComponents["1button5"] = new Button("5",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_5
		  );

      visualComponents["1button6"] = new Button("6",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_6
		  );

      visualComponents["1button7"] = new Button("7",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_7
		  );

      visualComponents["1button8"] = new Button("8",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_8
		  );

      visualComponents["1button9"] = new Button("9",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_9
		  );

      visualComponents["1button0"] = new Button("0",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_0
		  );

      visualComponents["1buttonBack"] = new Button("Back",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_BACK
		  );

      visualComponents["1buttonClear"] = new Button("C",
        font32,
        White,
        MathUtils::getCenteredPosition(engine.getSize(), ButtonSize),
        ButtonSize,
        ButtonColor,
        ButtonHoverColor,
        BUTTON_CLICK_C
		  );

      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button0"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button0"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button1"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button1"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button2"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button2"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button3"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button3"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button4"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button4"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button5"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button5"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button6"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button6"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button7"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button7"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button8"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button8"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1button9"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1button9"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1buttonClear"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1buttonClear"]));
      eventManager.subscribe(SDL_MOUSEMOTION, ((Button *)visualComponents["1buttonBack"])); eventManager.subscribe(SDL_MOUSEBUTTONDOWN, ((Button *)visualComponents["1buttonBack"]));

      // First row
      buttonGrid->addButton((Button *)visualComponents["1button1"]); buttonGrid->addButton((Button *)visualComponents["1button2"]); buttonGrid->addButton((Button *)visualComponents["1button3"]);
      // Second row
      buttonGrid->addButton((Button *)visualComponents["1button4"]); buttonGrid->addButton((Button *)visualComponents["1button5"]); buttonGrid->addButton((Button *)visualComponents["1button6"]);
      // Third row
      buttonGrid->addButton((Button *)visualComponents["1button7"]); buttonGrid->addButton((Button *)visualComponents["1button8"]); buttonGrid->addButton((Button *)visualComponents["1button9"]);
      // Fourth row
      buttonGrid->addButton((Button *)visualComponents["1buttonClear"]); buttonGrid->addButton((Button *)visualComponents["1button0"]); buttonGrid->addButton((Button *)visualComponents["1buttonBack"]);

      buttonGrid->setPosition(Vector2i(MathUtils::getCenteredPositionX(engine.getWidth(), buttonGrid->getSize().x), 50));
    
      dialogManager = new DialogManager(3, ((Image*)visualComponents["3Banner"]));
      dialogManager->addDialog(firstDialog);
      dialogManager->addDialog(secondDialog);
      dialogManager->addDialog(thirdDialog);
      dialogManager->activateDialog();
    }

    /// @brief Décharge la scène
    void unload() {
      for(auto it : buttonGrid->getList()) {
        eventManager.unsubscribe(SDL_MOUSEMOTION, it);
        eventManager.unsubscribe(SDL_MOUSEBUTTONDOWN, it);
      }
      for (auto it : visualComponents)
       delete it.second;

      delete buttonGrid;
      delete dialogManager;
      visualComponents.clear();
    }

    /// @brief Gère le rendu de la scène
    void handleRender() {
      glClear(GL_COLOR_BUFFER_BIT);
      for (auto it : visualComponents)
			  it.second->render();
      Engine::getInstance().swapWindow();
    }

    void addCharToCode(char enteredChar) {
      if(enteredCode.size() < 8) {
        enteredCode.push_back(enteredChar);
        ((Label*)visualComponents["enteredCode"])->setText(enteredCode);
      }
    }

    /// @brief Gère les événements de la scène
    void handleEvent() {
      switch (Event::getType()) {
        case SDL_USEREVENT:
          switch (Event::getUserEventCode()) {
            case BUTTON_CLICK_0: case BUTTON_CLICK_1: case BUTTON_CLICK_2:
            case BUTTON_CLICK_3: case BUTTON_CLICK_4: case BUTTON_CLICK_5:
            case BUTTON_CLICK_6: case BUTTON_CLICK_7: case BUTTON_CLICK_8:
            case BUTTON_CLICK_9: {
              char digit;
              switch (Event::getUserEventCode()) {
                case BUTTON_CLICK_0: digit = '0'; break;
                case BUTTON_CLICK_1: digit = '1'; break;
                case BUTTON_CLICK_2: digit = '2'; break;
                case BUTTON_CLICK_3: digit = '3'; break;
                case BUTTON_CLICK_4: digit = '4'; break;
                case BUTTON_CLICK_5: digit = '5'; break;
                case BUTTON_CLICK_6: digit = '6'; break;
                case BUTTON_CLICK_7: digit = '7'; break;
                case BUTTON_CLICK_8: digit = '8'; break;
                case BUTTON_CLICK_9: digit = '9'; break;
              }
              addCharToCode(digit);
              ((LabelWrapper *)visualComponents["labelWrapper"])->updateLabelPosition();
              break;
            }
            case BUTTON_CLICK_C:
                enteredCode = "";
                ((Label*)visualComponents["enteredCode"])->setText(enteredCode);
                ((LabelWrapper *)visualComponents["labelWrapper"])->updateLabelPosition();
                break;
            case BUTTON_CLICK_BACK:
                enteredCode.pop_back();
                ((Label*)visualComponents["enteredCode"])->setText(enteredCode);
                ((LabelWrapper *)visualComponents["labelWrapper"])->updateLabelPosition();
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
        default:
          if(dialogManager->isDialogActive()) {
            SDL_SetRelativeMouseMode(SDL_TRUE);
            buttonGrid->disableButtons();
            dialogManager->setCurrentVisible();
          } else {
            if(!buttonGrid->isButtonsEnable()) {
              SDL_SetRelativeMouseMode(SDL_FALSE);
              buttonGrid->enableButtons();
            }
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