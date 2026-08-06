#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "VisualComponent.hpp"
#include "../Assets/Texture.hpp"

/// @class Image
/// @brief Classe utilisée pour afficher des images.
class Image : public VisualComponent {
private:
	Texture* texture; ///< Texture de l'image.
	bool resizedX = false; ///< Indicateur de redimensionnement sur l'axe X
	bool resizedY = false; ///< Indicateur de redimensionnement sur l'axe Y
	Vector2i originalSize; ///< Taille originale de l'image

public:
	/// @brief Constructeur.
	/// @param pos Référence à la position de l'image.
	/// @param size Référence à la taille de l'image.
	/// @param texture Réference a la texture
	Image(Vector2i pos, Vector2i size, Texture* texture) : 
		VisualComponent(pos, size), 
		texture(texture),
		originalSize(size) 
	{}

	~Image() {}

	/// @brief Rendre l'image à l'écran.
	virtual void render() {
		if (texture) {
			texture->bind();
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);glVertex2i(pos.x, pos.y);
				glTexCoord2f(1,0);glVertex2i(pos.x + size.x, pos.y);
				glTexCoord2f(1,1);glVertex2i(pos.x + size.x, pos.y + size.y);
				glTexCoord2f(0,1);glVertex2i(pos.x, pos.y + size.y);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}	
	}

	/// @brief Change l'image affichée par le composant.
	/// @param texture Texture à utiliser.
	/// @return true si la texture est valide, false sinon
	bool changeImage(Texture* texture) {
		if (texture) {
			this->texture = texture;
			return true;
			}
		return false;
	}

	/// @brief Redimensionne l'image.
	/// @param newWidth Nouvelle largeur de l'image
	/// @param newHeight Nouvelle hauteur de l'image
	void resize(int newWidth, int newHeight) {
		size.x = newWidth;
		size.y = newHeight;
	}

	/// @brief Vérifie si l'image a été redimensionnée sur l'axe X.
	/// @return true si redimensionnée sur X, false sinon
	bool isResizedX() {
		return resizedX;
	}

	/// @brief Vérifie si l'image a été redimensionnée sur l'axe Y.
	/// @return true si redimensionnée sur Y, false sinon
	bool isResizedY() {
		return resizedY;
	}

	/// @brief Réinitialise l'image à sa taille originale.
	void resetSize() {
		size = originalSize;
		resizedX = false;
		resizedY = false;
		}
};