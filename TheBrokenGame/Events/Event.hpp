/// @file Events/Event.hpp
/// @brief Fichier contenant la classe Event
/// @author Dylan Allaire-Drolet

#pragma once
#include <SDL2/SDL.h>
#include <string>

/// @class Event
/// @brief Classe qui gère les événements SDL et les événements personnalisés
class Event {
	private:
		static SDL_Event event; ///< Événement SDL
		static float xScale; ///< Mise à l'échelle sur l'axe des x
		static float yScale; ///< Mise à l'échelle sur l'axe des y

	public:
		/// @brief Vérifie si un événement est en attente
		/// @return Retourne 1 (vrai) si un événement est en attente, 0 (faux) sinon
		static bool poll() {
			return SDL_PollEvent(&event);
		}

		/// @brief Trouve le type de l'événement actuel
		/// @return Retourne le type de l'événement actuel
		static unsigned int getType() {
			return event.type;
		}

		/// @brief Trouve la touche de la souris qui a été appuyée
		/// @return Retourne la touche de la souris qui a été appuyée
		static unsigned char getMouseButton() {
			return event.button.button;
		}

		/// @brief Obtient le code de la clé appuyée
		/// @return Le code de la clé appuyée
		static SDL_Keycode getKeyCode() {
			return event.key.keysym.sym;
		}

		/// @brief Obtention de la position de la souris
		/// @return Position de la souris selon la mise à l'échelle
		static SDL_Point getMousePosition() {
			return { (int)(event.motion.x / xScale), (int)(event.motion.y / yScale) };
		}

		/// @brief Obtention de la position relative de la souris
		/// @return Position relative de la souris selon la mise à l'échelle
		static SDL_Point getRelativeMotion() {
			return { (int)(event.motion.xrel / xScale), (int)(event.motion.yrel / yScale) };
		}

		/// @brief Pousse un événement personnalisé dans la file d'événements
		/// @param code Code de l'événement personnalisé dans /Events/Events.hpp
		/// @param isUserEvent Booléen indiquant si l'événement est un événement utilisateur
		static void push(unsigned int code, bool isUserEvent = true) {
			if (isUserEvent) {
				event.type = SDL_USEREVENT;
				event.user.code = code;
			}
			else {
				event.type = code;
			}
			SDL_PushEvent(&event);
		}

		/// @brief Trouve le code de l'événement personnalisé
		/// @return Retourne le code de l'événement personnalisé
		static unsigned int getUserEventCode() {
			return event.user.code;
		}

		/// @brief Détermination de la mise à l'échelle
		/// @param x Mise à l'échelle, en pixels, sur l'axe des x.
		/// @param y Mise à l'échelle, en pixels, sur l'axe des y.
		static void setScale(float x, float y) {
			xScale = x;
			yScale = y;
		}

		/// @brief Vérifie si une touche est enfoncée
		/// @param key Code de la touche
		/// @return Retourne 1 (vrai) si la touche est enfoncée, 0 (faux) sinon
		static bool isKeyDown(SDL_Keycode key){
			const Uint8* keystate = SDL_GetKeyboardState(NULL);
			return (bool)keystate[SDL_GetScancodeFromKey(key)];
		}

		/// @brief Obtient le texte de l'événement de texte
		/// @return Retourne le texte de l'événement de texte
		static std::string getTextInput(){
			return event.text.text;
		}
};

SDL_Event Event::event;
float Event::xScale = 1.0;
float Event::yScale = 1.0;
