#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Asset.hpp"

/// @class Texture
/// @brief Représente une texture dans le jeu MiniGolf, utilisant OpenGL.
class Texture : public Asset {
private:
	GLuint textureId; ///< Identifiant de la texture OpenGL.
	int width;        ///< Largeur de la texture en pixels.
	int height;       ///< Hauteur de la texture en pixels.

public:
	/// @brief Constructeur de la classe Texture à partir d'un fichier.
	/// @param filepath Chemin d'accès au fichier de texture (format image).
	/// @details Charge la texture à partir du fichier spécifié et initialise
	///          les membres de la classe. En cas d'échec du chargement,
	///          une exception est levée avec un message d'erreur.
	Texture(const std::string &filepath) 
		: textureId(0), width(0), height(0) {
		
		SDL_Surface* sdlSurface = IMG_Load(filepath.c_str());
		if (!sdlSurface) {
			throw std::runtime_error("Échec du chargement de la texture : " + std::string(IMG_GetError()));
		}

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 
					 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

		width = sdlSurface->w;
		height = sdlSurface->h;

		SDL_FreeSurface(sdlSurface);
	}

	/// @brief Constructeur de la classe Texture à partir d'une SDL_Surface.
	/// @param sdlSurface Pointeur vers une surface SDL existante.
	/// @details Initialise la texture à partir d'une surface SDL existante.
	///          Une exception est levée si la surface est invalide.
	Texture(SDL_Surface* sdlSurface) 
		: textureId(0), width(0), height(0) {
		if (!sdlSurface) {
			throw std::runtime_error("Surface SDL invalide !");
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 
					 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

		width = sdlSurface->w;
		height = sdlSurface->h;
	}

	/// @brief Destructeur de la classe Texture.
	/// @details Libère les ressources allouées pour la texture lors de la destruction de l'objet.
	~Texture() {
		if (textureId != 0) {
			glDeleteTextures(1, &textureId);
		}
	}

	/// @brief Lie la texture pour le rendu dans OpenGL.
	/// @details Cette méthode doit être appelée avant d'utiliser la texture 
	///          dans les opérations de rendu.
	void bind() {
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	/// @brief Récupère l'identifiant de la texture OpenGL.
	/// @return Identifiant de la texture OpenGL.
	GLuint getTextureId() {
		return textureId;
	}

	/// @brief Récupère le type de l'asset.
	/// @return Chaîne de caractères représentant le type de l'asset 
	///         ('Texture' pour une texture).
	std::string getType() {
		return "Texture";
	}

	/// @brief Récupère la hauteur de la texture.
	/// @return Hauteur de la texture en pixels.
	int getHeight() {
		return height;
	}

	/// @brief Récupère la largeur de la texture.
	/// @return Largeur de la texture en pixels.
	int getWidth() {
		return width;
	}
};
