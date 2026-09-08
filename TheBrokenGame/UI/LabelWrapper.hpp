#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "VisualComponent.hpp"
#include "Label.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"


/// @class Button
/// @brief Représente un Conteneur de Label
class LabelWrapper : public VisualComponent { 
private:
	Label* label; ///< Étiquette
	SDL_Color color; ///< Couleur
  int thickness;
  
public: 
  /// @brief Conteneur de Label
  /// @param pos position
  /// @param size grosseur
  /// @param color couleur du contour
  /// @param label text associe
  /// @param thickness epaisseur du contour
  LabelWrapper(Vector2i pos, Vector2i size, SDL_Color color, Label *label, int thickness) : VisualComponent(pos, size) {
    this->label = label;
    this->color = color;
    this->thickness = thickness;
    updateLabelPosition();
  }

	/// @brief Destructeur
	~LabelWrapper() {}


	/// @brief Afficher le bouton et son étiquette
	void render() {
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      int x = this->getPos().x;
      int y = this->getPos().y;
      int w = this->getSize().x;
      int h = this->getSize().y;
      int t = this->thickness;

      glBegin(GL_QUADS);
        // Bord supérieur
        glVertex2i(x, y);
        glVertex2i(x + w, y);
        glVertex2i(x + w, y + t);
        glVertex2i(x, y + t);

        // Bord inférieur
        glVertex2i(x, y + h - t);
        glVertex2i(x + w, y + h - t);
        glVertex2i(x + w, y + h);
        glVertex2i(x, y + h);

        // Bord gauche
        glVertex2i(x, y + t);
        glVertex2i(x + t, y + t);
        glVertex2i(x + t, y + h - t);
        glVertex2i(x, y + h - t);

        // Bord droit
        glVertex2i(x + w - t, y + t);
        glVertex2i(x + w, y + t);
        glVertex2i(x + w, y + h - t);
        glVertex2i(x + w - t, y + h - t);
      glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	void updateLabelPosition() {
		Vector2i centered = MathUtils::getCenteredPosition(this->getSize(), this->label->getSize());
		this->label->setPosition(Vector2i(this->getPos().x + centered.x, this->getPos().y + centered.y));
	}
};