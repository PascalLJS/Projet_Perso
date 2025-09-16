#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../DP/Singleton.hpp"
#include "../Scene/SceneManager.hpp"
#include "../Assets/AssetManager.hpp"
#include "../Events/Event.hpp"
#include "../Events/Events.hpp"
#include "../Math/Vector2i.hpp"
#include "../Time/Stopwatch.hpp"

/// @brief Classe du moteur
class Engine : public Singleton<Engine> {
private :
	bool isUp; ///< Booléen indiquant si le jeu est marche
	SDL_Window* sdlWindow; ///< Fenêtre SDL
	SDL_GLContext glContext; ///< Le renderer
	Vector2i windowSize; ///< Taille de la fenêtre
	Stopwatch stopWatch; ///< Chronomètre


	/// @brief Crée la fenêtre
	/// @param config Contient les paramètres de configuration
	void createWindow() {
  	sdlWindow = SDL_CreateWindow("Vaisseau", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL);
		glContext = SDL_GL_CreateContext(sdlWindow);
	}

public :  
	SceneManager sceneManager; ///< Gestionnaire de scènes
	AssetManager assetManager; ///< Gestionnaire de ressources

	/// @brief Constructeur du moteur
	Engine() {
		TTF_Init();
		isUp = !SDL_Init(SDL_INIT_VIDEO);
		windowSize.x = 800, windowSize.y = 600;
		createWindow();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_COLOR);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	/// @brief Détruit la fenêtre et le renderer
	~Engine() {
		SDL_DestroyWindow(sdlWindow);
		SDL_GL_DeleteContext(glContext);
	}

	/// @brief Obtient la largeur de la fenêtre
	/// @return La largeur en int
	int getWidth() {
		return windowSize.x;
	}

	/// @brief Obtient la hauteur de la fenêtre
	/// @return La hauteur en int
	int getHeight() {
		return windowSize.y;
	}

	/// @brief Rafraichit la fenêtre
	void swapWindow() {
		SDL_GL_SwapWindow(sdlWindow);
	}

	/// @brief Lance la boucle de jeu
	void start() {
		while(isUp) {
			while(Event::poll()) {
				switch(Event::getType()) {
					case SDL_USEREVENT:
						if (Event::getUserEventCode() == Events::QUIT_APPLICATION) {
							SDL_DestroyWindow(sdlWindow); sdlWindow = nullptr;
							isUp = false;
						}
						else
							sceneManager.getCurrentScene().handleEvent();
						break;

					case SDL_QUIT :
						isUp = false;
						break;

					default:
						sceneManager.getCurrentScene().handleEvent();
						break;
				}
			}
			sceneManager.getCurrentScene().handleUpdate(stopWatch.getElapsedSeconds());
			stopWatch.Restart();
			sceneManager.getCurrentScene().handleRender();
	  }
	}
};