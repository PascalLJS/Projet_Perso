#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Asset.hpp"

/// @class Color
/// @brief Représente une couleur dans le jeu MiniGolf.
class Color : public Asset {
private:
	SDL_Color color; ///< Composants de la couleur (rouge, vert, bleu, alpha).

public:
	/// @brief Constructeur de la classe Color.
	/// @param red Composante rouge (0-255).
	/// @param green Composante verte (0-255).
	/// @param blue Composante bleue (0-255).
	/// @param alpha Composante alpha (0-255).
	/// @details Initialise les composants de la couleur avec les valeurs fournies.
	Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha){
		color.r = red; ///< Initialisation de la composante rouge.
		color.g = green; ///< Initialisation de la composante verte.
		color.b = blue; ///< Initialisation de la composante bleue.
		color.a = alpha; ///< Initialisation de la composante alpha.
	}

	/// @brief Récupère la composante rouge.
	/// @return Valeur de la composante rouge (0-255).
	GLubyte getRed() { return color.r; }

	/// @brief Récupère la composante verte.
	/// @return Valeur de la composante verte (0-255).
	GLubyte getGreen() { return color.g; }

	/// @brief Récupère la composante bleue.
	/// @return Valeur de la composante bleue (0-255).
	GLubyte getBlue() { return color.b; }

	/// @brief Récupère la composante alpha.
	/// @return Valeur de la composante alpha (0-255).
	GLubyte getAlpha() { return color.a; }

	/// @brief Définit la couleur dans OpenGL.
	/// @details Applique la couleur actuelle en utilisant la fonction
	///          glColor4ub d'OpenGL pour le rendu.
	void applyColor() {
		glColor4ub(color.r, color.g, color.b, color.a);
	}

	/// @brief Récupère la couleur au format SDL_Color.
	/// @return Structure SDL_Color représentant la couleur.
	SDL_Color getSDLColor() {
		return color;
	}

	/// @brief Récupère le type de l'asset.
	/// @return Chaîne de caractères représentant le type de l'asset 
	///         ('Color' pour une couleur).
	std::string getType() {
		return "Color";
	}
};
