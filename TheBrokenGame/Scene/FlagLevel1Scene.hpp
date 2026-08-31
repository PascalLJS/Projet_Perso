#pragma once

#include "../Engine/Engine.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/Events.hpp"
#include "../UI/VisualComponent.hpp"
#include "../Math/MathUtils.hpp"
#include "../Math/Matrix.hpp"
#include "../UI/Line.hpp"
#include "Scene.hpp"
#include <map>

/// @class Level2Scene
/// @brief Représente la scène de jeu
class FlagLevel1Scene : public Scene {
private:
	EventManager eventManager;	///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> VisualComponentsFinal;
  std::map<string, Line*> LineToTransit;
  std::map<string, Vector2i> lineTransition;
  std::map<string, Vector2i> finalDestination;
	
public:

  void transitLine(std::map<string, Vector2i> transition, std::map<string, Vector2i> destination, std::map<string, Line*> components){
    for(auto transitVector : transition) {
      if(destination[transitVector.first] != components[transitVector.first]->getPosStart()){
        components[transitVector.first]->setPosStart(components[transitVector.first]->getPosStart() + transitVector.second);
        components[transitVector.first]->setPosEnd(components[transitVector.first]->getPosEnd() + transitVector.second);
      }
    }
  }

	/// @brief Charge la scène
	void load() {
    SDL_Color lineColor = engine.assetManager.getAsset<Color *>("WhitePure")->getSDLColor();
		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

    VisualComponentsFinal["Banner"] = new Image(Vector2i(25, 25), Vector2i(800, 150), engine.assetManager.getAsset<Texture*>("Dialog"));
    
    lineTransition["1"] = Vector2i(-1, 1);
    finalDestination["1"] = Vector2i(130, 400);

    lineTransition["2"] = Vector2i(1, 2);
    finalDestination["2"] = Vector2i(220, 400);

    lineTransition["3"] = Vector2i(1, 1);
    finalDestination["3"] = Vector2i(201, 400);

    lineTransition["4"] = Vector2i(-3, 1);
    finalDestination["4"] = Vector2i(160, 449);

    lineTransition["5"] = Vector2i(-4, 0);
    finalDestination["5"] = Vector2i(295, 425);

    lineTransition["6"] = Vector2i(2,0);
    finalDestination["6"] = Vector2i(305, 400);

    lineTransition["7"] = Vector2i(-2, 1);
    finalDestination["7"] = Vector2i(310, 400);

    lineTransition["8"] = Vector2i(0, 1);
    finalDestination["8"] = Vector2i(335, 450);

    lineTransition["9"] = Vector2i(2, 1);
    finalDestination["9"] = Vector2i(352, 400);

    lineTransition["10"] = Vector2i(-2, 0);
    finalDestination["10"] = Vector2i(425, 400);

    lineTransition["11"] = Vector2i(-2, 2);
    finalDestination["11"] = Vector2i(430, 425);

    lineTransition["12"] = Vector2i(1, 1);
    finalDestination["12"] = Vector2i(485,400);

    lineTransition["13"] = Vector2i(0, 1);
    finalDestination["13"] = Vector2i(472,425);

    lineTransition["14"] = Vector2i(1, 1);
    finalDestination["14"] = Vector2i(490,400);

    lineTransition["15"] = Vector2i(-2, 1);
    finalDestination["15"] = Vector2i(502,445);

    lineTransition["16"] = Vector2i(-3, 2);
    finalDestination["16"] = Vector2i(520,450);

    lineTransition["17"] = Vector2i(1, -1);
    finalDestination["17"] = Vector2i(561,400);

    lineTransition["18"] = Vector2i(2, 4);
    finalDestination["18"] = Vector2i(592,400);

    lineTransition["19"] = Vector2i(2, 0);
    finalDestination["19"] = Vector2i(610,425);

    lineTransition["20"] = Vector2i(3, 0);
    finalDestination["20"] = Vector2i(640,400);

    lineTransition["21"] = Vector2i(-1, 1);
    finalDestination["21"] = Vector2i(670,400);

    lineTransition["22"] = Vector2i(4, 1);
    finalDestination["22"] = Vector2i(700,400);

    lineTransition["23"] = Vector2i(1, 0);
    finalDestination["23"] = Vector2i(741,400);

    lineTransition["24"] = Vector2i(0, 1);
    finalDestination["24"] = Vector2i(760,400);

    lineTransition["25"] = Vector2i(3, 1);
    finalDestination["25"] = Vector2i(760,425);

    // Lettre F
    LineToTransit["1"] = new Line(Vector2i(180,350), Vector2i(180,400), lineColor);
    VisualComponentsFinal["line1"] = new Line(Vector2i(130,400), Vector2i(155,400), lineColor);
    VisualComponentsFinal["line2"] = new Line(Vector2i(130,425), Vector2i(140,425), lineColor);
    
    // Lettre L
    VisualComponentsFinal["line3"] = new Line(Vector2i(160,400), Vector2i(160,450), lineColor);
    LineToTransit["4"] = new Line(Vector2i(310,399), Vector2i(335,399), lineColor);

    // Lettre A
    LineToTransit["3"] = new Line(Vector2i(176,375), Vector2i(165,425), lineColor);
    VisualComponentsFinal["line6"] = new Line(Vector2i(201,400), Vector2i(215,450), lineColor);
    VisualComponentsFinal["line7"] = new Line(Vector2i(195,425), Vector2i(208,425), lineColor);

    // Lettre G
    LineToTransit["2"] = new Line(Vector2i(170,300), Vector2i(170,350), lineColor);
    VisualComponentsFinal["line9"] = new Line(Vector2i(220,400), Vector2i(245,400), lineColor);
    VisualComponentsFinal["line10"] = new Line(Vector2i(220,450), Vector2i(245,450), lineColor);
    VisualComponentsFinal["line11"] = new Line(Vector2i(245,450), Vector2i(245,425), lineColor);
    VisualComponentsFinal["line12"] = new Line(Vector2i(245,425), Vector2i(230,425), lineColor);

    // Lettre {
    VisualComponentsFinal["line13"] = new Line(Vector2i(270,400), Vector2i(260,400), lineColor);
    VisualComponentsFinal["line14"] = new Line(Vector2i(260,400), Vector2i(255,410), lineColor);
    VisualComponentsFinal["line15"] = new Line(Vector2i(255,410), Vector2i(260,420), lineColor);
    VisualComponentsFinal["line16"] = new Line(Vector2i(260,420), Vector2i(250,425), lineColor);
    VisualComponentsFinal["line17"] = new Line(Vector2i(250,425), Vector2i(260,430), lineColor);
    VisualComponentsFinal["line18"] = new Line(Vector2i(260,430), Vector2i(255,440), lineColor);
    VisualComponentsFinal["line19"] = new Line(Vector2i(255,440), Vector2i(260,450), lineColor);
    VisualComponentsFinal["line20"] = new Line(Vector2i(260,450), Vector2i(270,450), lineColor);

    // Lettre 7
    VisualComponentsFinal["line23"] = new Line(Vector2i(280,400), Vector2i(305,400), lineColor);
    LineToTransit["6"] = new Line(Vector2i(255,400), Vector2i(235,450), lineColor);
    LineToTransit["5"] = new Line(Vector2i(495,425), Vector2i(482,425), lineColor);

    // Lettre G
    VisualComponentsFinal["line26"] = new Line(Vector2i(310,400), Vector2i(310,450), lineColor);
    LineToTransit["7"] = new Line(Vector2i(410,350), Vector2i(435,350), lineColor);
    VisualComponentsFinal["line28"] = new Line(Vector2i(310,450), Vector2i(335,450), lineColor);
    LineToTransit["8"] = new Line(Vector2i(335,350), Vector2i(335,325), lineColor);
    VisualComponentsFinal["line30"] = new Line(Vector2i(335,425), Vector2i(320,425), lineColor);

    // Lettre J
    VisualComponentsFinal["line31"] = new Line(Vector2i(340,400), Vector2i(365,400), lineColor);
    LineToTransit["9"] = new Line(Vector2i(252,350), Vector2i(252,395), lineColor);
    VisualComponentsFinal["line33"] = new Line(Vector2i(352,445), Vector2i(347,450), lineColor);
    VisualComponentsFinal["line34"] = new Line(Vector2i(347,450), Vector2i(340,450), lineColor);

    // Lettre T
    VisualComponentsFinal["10"] = new Line(Vector2i(370,400), Vector2i(395,400), lineColor);
    VisualComponentsFinal["line36"] = new Line(Vector2i(382,400), Vector2i(382,450), lineColor);

    // Lettre P
    VisualComponentsFinal["line37"] = new Line(Vector2i(400,400), Vector2i(400,450), lineColor);
    VisualComponentsFinal["line38"] = new Line(Vector2i(400,400), Vector2i(425,400), lineColor);
    LineToTransit["10"] = new Line(Vector2i(625,400), Vector2i(625,425), lineColor);
    VisualComponentsFinal["line40"] = new Line(Vector2i(425,425), Vector2i(400,425), lineColor);

    // Lettre -
    LineToTransit["11"] = new Line(Vector2i(630,225), Vector2i(655,225), lineColor);

    // Lettre Y
    VisualComponentsFinal["line42"] = new Line(Vector2i(460,400), Vector2i(472,425), lineColor);
    LineToTransit["12"] = new Line(Vector2i(435,350), Vector2i(422,375), lineColor);
    LineToTransit["13"] = new Line(Vector2i(472,325), Vector2i(472,350), lineColor);

    // Lettre J
    LineToTransit["14"] = new Line(Vector2i(390,300), Vector2i(415,300), lineColor);
    VisualComponentsFinal["line46"] = new Line(Vector2i(502,400), Vector2i(502,445), lineColor);
    LineToTransit["15"] = new Line(Vector2i(602,395), Vector2i(597,400), lineColor);
    VisualComponentsFinal["line48"] = new Line(Vector2i(497,450), Vector2i(490,450), lineColor);

    // Lettre L
    VisualComponentsFinal["line49"] = new Line(Vector2i(520,400), Vector2i(520,450), lineColor);
    LineToTransit["16"] = new Line(Vector2i(670,350), Vector2i(695,350), lineColor);

    // Lettre A
    VisualComponentsFinal["line51"] = new Line(Vector2i(561,400), Vector2i(550,450), lineColor);
    LineToTransit["17"] = new Line(Vector2i(511,450), Vector2i(525,500), lineColor);
    VisualComponentsFinal["line53"] = new Line(Vector2i(555,425), Vector2i(568,425), lineColor);

    // Lettre I
    VisualComponentsFinal["line54"] = new Line(Vector2i(586,400), Vector2i(598,400), lineColor);
    LineToTransit["18"] = new Line(Vector2i(442,100), Vector2i(442,150), lineColor);
    VisualComponentsFinal["line82"] = new Line(Vector2i(586,450), Vector2i(598,450), lineColor);

    // Lettre -
    LineToTransit["19"] = new Line(Vector2i(410,425), Vector2i(435,425), lineColor);

    // Lettre K
    LineToTransit["20"] = new Line(Vector2i(340,400), Vector2i(340,450), lineColor);
    VisualComponentsFinal["line57"] = new Line(Vector2i(640,425), Vector2i(665,400), lineColor);
    VisualComponentsFinal["line58"] = new Line(Vector2i(640,425), Vector2i(665,450), lineColor);

    // Lettre J
    LineToTransit["21"] = new Line(Vector2i(720,350), Vector2i(745,350), lineColor);
    VisualComponentsFinal["line60"] = new Line(Vector2i(682,400), Vector2i(682,445), lineColor);
    VisualComponentsFinal["line61"] = new Line(Vector2i(682,445), Vector2i(677,450), lineColor);
    VisualComponentsFinal["line62"] = new Line(Vector2i(677,450), Vector2i(670,450), lineColor);

    // Lettre H
    LineToTransit["22"] = new Line(Vector2i(500,350), Vector2i(500,400), lineColor);
    VisualComponentsFinal["line64"] = new Line(Vector2i(725,400), Vector2i(725,450), lineColor);
    VisualComponentsFinal["line65"] = new Line(Vector2i(700,425), Vector2i(725,425), lineColor);

    // Lettre A
    VisualComponentsFinal["line66"] = new Line(Vector2i(741,400), Vector2i(730,450), lineColor);
    LineToTransit["23"] = new Line(Vector2i(691,400), Vector2i(705,450), lineColor);
    VisualComponentsFinal["line68"] = new Line(Vector2i(735,425), Vector2i(748,425), lineColor);

    // Lettre K
    LineToTransit["24"] = new Line(Vector2i(760,350), Vector2i(760,400), lineColor);
    LineToTransit["25"] = new Line(Vector2i(610,375), Vector2i(635,350), lineColor);
    VisualComponentsFinal["line71"] = new Line(Vector2i(760,425), Vector2i(785,450), lineColor);

    // Lettre I
    VisualComponentsFinal["line72"] = new Line(Vector2i(796,400), Vector2i(796,450), lineColor);
    VisualComponentsFinal["line83"] = new Line(Vector2i(790,400), Vector2i(802,400), lineColor);
    VisualComponentsFinal["line84"] = new Line(Vector2i(790,450), Vector2i(802,450), lineColor);

    // Lettre }
    VisualComponentsFinal["line73"] = new Line(Vector2i(810,400), Vector2i(820,400), lineColor);
    VisualComponentsFinal["line74"] = new Line(Vector2i(820,400), Vector2i(825,410), lineColor);
    VisualComponentsFinal["line75"] = new Line(Vector2i(825,410), Vector2i(820,420), lineColor);
    VisualComponentsFinal["line76"] = new Line(Vector2i(820,420), Vector2i(830,425), lineColor);
    VisualComponentsFinal["line77"] = new Line(Vector2i(830,425), Vector2i(820,430), lineColor);
    VisualComponentsFinal["line78"] = new Line(Vector2i(820,430), Vector2i(825,440), lineColor);
    VisualComponentsFinal["line79"] = new Line(Vector2i(825,440), Vector2i(820,450), lineColor);
    VisualComponentsFinal["line80"] = new Line(Vector2i(820,450), Vector2i(810,450), lineColor);
	}

	/// @brief Décharge la scène
	void unload() {
		for (auto it : VisualComponentsFinal)
			delete it.second;
		VisualComponentsFinal.clear();

    for (auto it : LineToTransit)
			delete it.second;
	  LineToTransit.clear();

	  lineTransition.clear();
    finalDestination.clear();
	}

	/// @brief Gère le rendu de la scène
	void handleRender() {
		glClear(GL_COLOR_BUFFER_BIT);
    for (auto it : LineToTransit)
			it.second->render();
    for (auto it : VisualComponentsFinal)
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
      case SDL_KEYDOWN:
					switch (Event::getKeyCode()) {
						case SDLK_ESCAPE:
							Event::push(SDL_QUIT, false);
							break;
            case SDLK_v:
              transitLine(lineTransition, finalDestination, LineToTransit);
              break;
            case SDLK_RETURN:
              engine.sceneManager.transitScene("Level2Scene");
              break;
			}
			default:
				eventManager.notify(Event::getType());
		}
	}

	/// @brief Gère les changements de la scène
	/// @param deltaTime Delta temps, en seconde, entre chaque rafraîchissement
	void handleUpdate(double deltaTime) {
		
	}
	
};