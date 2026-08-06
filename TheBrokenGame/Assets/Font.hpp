#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#include "Asset.hpp"


/// @class Font
/// @brief Représente une police de caractères dans le jeu MiniGolf.
class Font : public Asset {
private:
	TTF_Font* font; ///< Pointeur vers la police de caractères TTF.
	int size; ///< Taille de la police en points.

public:
	/// @brief Constructeur de la classe Font.
	/// @param filepath Chemin d'accès au fichier de police (format TTF).
	/// @param fontSize Taille de la police en points.
	/// @details Charge la police à partir du fichier spécifié et initialise
	Font(const std::string &filepath, const int fontSize) : size(fontSize) {
		font = TTF_OpenFont(filepath.c_str(), size);
	}

	/// @brief Destructeur de la classe Font.
	/// @details Libère les ressources allouées pour la police lors de la destruction de l'objet.
	~Font() {
		TTF_CloseFont(font);
	}

	/// @brief Récupère le pointeur vers la police de caractères.
	/// @return Pointeur vers l'objet TTF_Font.
	/// @details Permet d'accéder à la police de caractères pour le rendu
	///          ou d'autres opérations de traitement.
	TTF_Font* getFont() {
		return font;
	}

	/// @brief Récupère le type de l'asset.
	/// @return Chaîne de caractères représentant le type de l'asset 
	///         ('Font' pour une police de caractères).
	std::string getType() {
		return "Font";
	}
};
