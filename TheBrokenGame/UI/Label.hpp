#pragma once

#include <string>
#include <SDL2/SDL_opengl.h>

#include "../Math/Vector2i.hpp"
#include "VisualComponent.hpp"
#include "../Assets/Font.hpp"
#include "../Assets/Color.hpp"
#include "../Engine/Engine.hpp"

/// @class Label
/// @brief Une étiquette visuelle qui affiche du texte.
/// @details Afin d'assurer le bon fonctionnement, il est important d'avoir le blend d'activé
///		ainsi que le BlendFunc. Il est aussi recommandé d'être dans une projection ortographique.
class Label : public VisualComponent {
protected:
	Font* font; ///< La police d'écriture de l'étiquette
	SDL_Color textColor; ///< La couleur du texte lors du rendu
	uint32_t textureId; ///< L'identifiant de la texture associée avec l'étiquette
	std::string text; ///< Le texte dans le Label
	Vector2i labelRealSize;

	/// @brief Redessine le texte sur la texture
	virtual void renderText() {
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font->getFont(), text.c_str(), textColor);

		if (surf) {
			glBindTexture(GL_TEXTURE_2D, textureId);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, surf->pitch / surf->format->BytesPerPixel);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

			size.x = surf->w;
			size.y = surf->h;
		}

		SDL_FreeSurface(surf);
	}

public:
	/// @brief Constructeur de l'étiquette
	/// @param pos La position en haut à gauche sur l'écran
	/// @param fontResource La ressource de police de caractère
	/// @param startText (Optionnel) Le texte de départ de l'étiquette
	Label(Vector2i pos, Font* fontResource,  std::string startText = "Label", SDL_Color startColor = Engine::getInstance().assetManager.getAsset<Color*>("GrayDefault2")->getSDLColor()) : VisualComponent(pos) {
		this->font = fontResource;
		this->textColor = startColor;
		this->text = startText;

		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		renderText();
	}

		/// @brief Détruit l'étiquette et sa texture associée
	~Label() {
		glDeleteTextures(1, &textureId);
	}

	/// @brief Change le texte de l'étiquette et regénère la texture
	/// @param text Le texte à afficher
	/// @param color (Optionel) La couleur du texte
	void setText(std::string newText) {
		if (newText != text) {
			text = newText;
			renderText();
		}
	}

	/// @brief Change la couleur du texte et redessine la texture.
	/// @param color Un asset de couleur
	void setColor(Color* color) {
		SDL_Color c = color->getSDLColor();
		if (
			c.r != textColor.r
			|| c.g != textColor.g
			|| c.b != textColor.b
			|| c.a != textColor.a
		) {
			textColor = c;
			renderText();
		}
	}

	/// @brief Change la couleur du texte et redessine la texture.
	/// @param color Un struct de couleur SDL
	void setColor(SDL_Color color) {
		if (
			color.r != textColor.r
			|| color.g != textColor.g
			|| color.b != textColor.b
			|| color.a != textColor.a
		) {
			textColor = color;
			renderText();
		}
	}

	void setRealSize(Vector2i realSize){
		this->labelRealSize = realSize;
	}

	Vector2i getRealSize(){
		return labelRealSize;
	}

	/// @brief Dessiner l'étiquette sur la fenêtre
	void render() {
		glEnable(GL_TEXTURE_2D);
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glBegin(GL_QUADS);
			glColor4ub(255,255,255,255);

			glTexCoord2f(0.0, 0.0); glVertex2i(pos.x, pos.y);
			glTexCoord2f(1.0, 0.0); glVertex2i(pos.x + size.x, pos.y);
			glTexCoord2f(1.0, 1.0); glVertex2i(pos.x + size.x, pos.y + size.y);
			glTexCoord2f(0.0, 1.0); glVertex2i(pos.x, pos.y + size.y);
		glEnd();
		glEnableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
};