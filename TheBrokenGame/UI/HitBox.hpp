#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../Events/Event.hpp"
#include "../DP/Observer.hpp"
#include "VisualComponent.hpp"
#include "Label.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"


/// @class Button
/// @brief Représente un bouton
class HitBox : Observer{
private:
	SDL_Color color; ///< Couleur
  Vector2i pos;
  Vector2i size;
  
public: 
	  /// @brief Constructeur
    HitBox(Vector2i pos, Vector2i size) {

    }

	/// @brief Destructeur
	~HitBox(){}

 	/// @brief Envoie le code de l'événement s'il y a un clic avec le bouton gauche de la souris
 	void notification() {
	}
};