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
	EventManager eventManager;				///< Gestionnaire d'événements
	Engine &engine = Engine::getInstance(); ///< Instance du moteur
	Matrix projection;
	std::map<string, VisualComponent*> visualComponents;
	
public:
	/// @brief Charge la scène
	void load() {
    SDL_Color lineColor = engine.assetManager.getAsset<Color *>("WhitePure")->getSDLColor();
		projection.loadProjection(Engine::getInstance().getWidth(), Engine::getInstance().getHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(projection);

    // Lettre F
    visualComponents["line"] = new Line(Vector2i(130,400), Vector2i(130,450), lineColor);
    visualComponents["line1"] = new Line(Vector2i(130,400), Vector2i(155,400), lineColor);
    visualComponents["line2"] = new Line(Vector2i(130,425), Vector2i(140,425), lineColor);
    
    // Lettre L
    visualComponents["line3"] = new Line(Vector2i(160,400), Vector2i(160,450), lineColor);
    visualComponents["line4"] = new Line(Vector2i(160,449), Vector2i(185,449), lineColor);

    // Lettre A
    visualComponents["line5"] = new Line(Vector2i(201,400), Vector2i(190,450), lineColor);
    visualComponents["line6"] = new Line(Vector2i(201,400), Vector2i(215,450), lineColor);
    visualComponents["line7"] = new Line(Vector2i(195,425), Vector2i(208,425), lineColor);

    // Lettre G
    visualComponents["line8"] = new Line(Vector2i(220,400), Vector2i(220,450), lineColor);
    visualComponents["line9"] = new Line(Vector2i(220,400), Vector2i(245,400), lineColor);
    visualComponents["line10"] = new Line(Vector2i(220,450), Vector2i(245,450), lineColor);
    visualComponents["line11"] = new Line(Vector2i(245,450), Vector2i(245,425), lineColor);
    visualComponents["line12"] = new Line(Vector2i(245,425), Vector2i(230,425), lineColor);

    // Lettre {
    visualComponents["line13"] = new Line(Vector2i(270,400), Vector2i(260,400), lineColor);
    visualComponents["line14"] = new Line(Vector2i(260,400), Vector2i(255,410), lineColor);
    visualComponents["line15"] = new Line(Vector2i(255,410), Vector2i(260,420), lineColor);
    visualComponents["line16"] = new Line(Vector2i(260,420), Vector2i(250,425), lineColor);
    visualComponents["line17"] = new Line(Vector2i(250,425), Vector2i(260,430), lineColor);
    visualComponents["line18"] = new Line(Vector2i(260,430), Vector2i(255,440), lineColor);
    visualComponents["line19"] = new Line(Vector2i(255,440), Vector2i(260,450), lineColor);
    visualComponents["line20"] = new Line(Vector2i(260,450), Vector2i(270,450), lineColor);

    // Lettre 7
    visualComponents["line23"] = new Line(Vector2i(280,400), Vector2i(305,400), lineColor);
    visualComponents["line24"] = new Line(Vector2i(305,400), Vector2i(285,450), lineColor);
    visualComponents["line25"] = new Line(Vector2i(295,425), Vector2i(282,425), lineColor);

    // Lettre G
    visualComponents["line26"] = new Line(Vector2i(310,400), Vector2i(310,450), lineColor);
    visualComponents["line27"] = new Line(Vector2i(310,400), Vector2i(335,400), lineColor);
    visualComponents["line28"] = new Line(Vector2i(310,450), Vector2i(335,450), lineColor);
    visualComponents["line29"] = new Line(Vector2i(335,450), Vector2i(335,425), lineColor);
    visualComponents["line30"] = new Line(Vector2i(335,425), Vector2i(320,425), lineColor);

    // Lettre J
    visualComponents["line31"] = new Line(Vector2i(340,400), Vector2i(365,400), lineColor);
    visualComponents["line32"] = new Line(Vector2i(352,400), Vector2i(352,445), lineColor);
    visualComponents["line33"] = new Line(Vector2i(352,445), Vector2i(347,450), lineColor);
    visualComponents["line34"] = new Line(Vector2i(347,450), Vector2i(340,450), lineColor);

    // Lettre T
    visualComponents["line35"] = new Line(Vector2i(370,400), Vector2i(395,400), lineColor);
    visualComponents["line36"] = new Line(Vector2i(382,400), Vector2i(382,450), lineColor);

    // Lettre P
    visualComponents["line37"] = new Line(Vector2i(400,400), Vector2i(400,450), lineColor);
    visualComponents["line38"] = new Line(Vector2i(400,400), Vector2i(425,400), lineColor);
    visualComponents["line39"] = new Line(Vector2i(425,400), Vector2i(425,425), lineColor);
    visualComponents["line40"] = new Line(Vector2i(425,425), Vector2i(400,425), lineColor);
    // Lettre -
    visualComponents["line41"] = new Line(Vector2i(430,425), Vector2i(455,425), lineColor);

    // Lettre Y
    visualComponents["line42"] = new Line(Vector2i(460,400), Vector2i(472,425), lineColor);
    visualComponents["line43"] = new Line(Vector2i(485,400), Vector2i(472,425), lineColor);
    visualComponents["line44"] = new Line(Vector2i(472,425), Vector2i(472,450), lineColor);

    // Lettre J
    visualComponents["line45"] = new Line(Vector2i(490,400), Vector2i(515,400), lineColor);
    visualComponents["line46"] = new Line(Vector2i(502,400), Vector2i(502,445), lineColor);
    visualComponents["line47"] = new Line(Vector2i(502,445), Vector2i(497,450), lineColor);
    visualComponents["line48"] = new Line(Vector2i(497,450), Vector2i(490,450), lineColor);

    // Lettre L
    visualComponents["line49"] = new Line(Vector2i(520,400), Vector2i(520,450), lineColor);
    visualComponents["line50"] = new Line(Vector2i(520,450), Vector2i(545,450), lineColor);

    // Lettre A
    visualComponents["line51"] = new Line(Vector2i(561,400), Vector2i(550,450), lineColor);
    visualComponents["line52"] = new Line(Vector2i(561,400), Vector2i(575,450), lineColor);
    visualComponents["line53"] = new Line(Vector2i(555,425), Vector2i(568,425), lineColor);

    // Lettre I
    visualComponents["line54"] = new Line(Vector2i(586,400), Vector2i(598,400), lineColor);
    visualComponents["line81"] = new Line(Vector2i(592,400), Vector2i(592,450), lineColor);
    visualComponents["line82"] = new Line(Vector2i(586,450), Vector2i(598,450), lineColor);

    // Lettre -
    visualComponents["line55"] = new Line(Vector2i(610,425), Vector2i(635,425), lineColor);

    // Lettre K
    visualComponents["line56"] = new Line(Vector2i(640,400), Vector2i(640,450), lineColor);
    visualComponents["line57"] = new Line(Vector2i(640,425), Vector2i(665,400), lineColor);
    visualComponents["line58"] = new Line(Vector2i(640,425), Vector2i(665,450), lineColor);

    // Lettre J
    visualComponents["line59"] = new Line(Vector2i(670,400), Vector2i(695,400), lineColor);
    visualComponents["line60"] = new Line(Vector2i(682,400), Vector2i(682,445), lineColor);
    visualComponents["line61"] = new Line(Vector2i(682,445), Vector2i(677,450), lineColor);
    visualComponents["line62"] = new Line(Vector2i(677,450), Vector2i(670,450), lineColor);

    // Lettre H
    visualComponents["line63"] = new Line(Vector2i(700,400), Vector2i(700,450), lineColor);
    visualComponents["line64"] = new Line(Vector2i(725,400), Vector2i(725,450), lineColor);
    visualComponents["line65"] = new Line(Vector2i(700,425), Vector2i(725,425), lineColor);

    // Lettre A
    visualComponents["line66"] = new Line(Vector2i(741,400), Vector2i(730,450), lineColor);
    visualComponents["line67"] = new Line(Vector2i(741,400), Vector2i(755,450), lineColor);
    visualComponents["line68"] = new Line(Vector2i(735,425), Vector2i(748,425), lineColor);

    // Lettre K
    visualComponents["line69"] = new Line(Vector2i(760,400), Vector2i(760,450), lineColor);
    visualComponents["line70"] = new Line(Vector2i(760,425), Vector2i(785,400), lineColor);
    visualComponents["line71"] = new Line(Vector2i(760,425), Vector2i(785,450), lineColor);

    // Lettre I
    visualComponents["line72"] = new Line(Vector2i(792,400), Vector2i(792,450), lineColor);

    // Lettre }
    visualComponents["line73"] = new Line(Vector2i(810,400), Vector2i(820,400), lineColor);
    visualComponents["line74"] = new Line(Vector2i(820,400), Vector2i(825,410), lineColor);
    visualComponents["line75"] = new Line(Vector2i(825,410), Vector2i(820,420), lineColor);
    visualComponents["line76"] = new Line(Vector2i(820,420), Vector2i(830,425), lineColor);
    visualComponents["line77"] = new Line(Vector2i(830,425), Vector2i(820,430), lineColor);
    visualComponents["line78"] = new Line(Vector2i(820,430), Vector2i(825,440), lineColor);
    visualComponents["line79"] = new Line(Vector2i(825,440), Vector2i(820,450), lineColor);
    visualComponents["line80"] = new Line(Vector2i(820,450), Vector2i(810,450), lineColor);
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