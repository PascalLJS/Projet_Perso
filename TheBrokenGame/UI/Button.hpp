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
class Button : public VisualComponent, public Observer {
private:
	Label* label; ///< Étiquette
	SDL_Color color; ///< Couleur
	SDL_Color hoverColor; ///< Couleur lorsque survolé
	SDL_Color disableColor; ///< Couleur lorsque désactivé
	bool hover; ///< Si survolé
	unsigned int eventCode; ///< Code d'événement lorsque cliqué
	bool enable; ///< Si le bouton peut être cliqué
  
public: 
	/// @brief Constructeur
    /// @param text Texte pour l'étiquette
    /// @param fontResource Pointeur d'un font
    /// @param labelColor Couleur du texte dans l'étiquette 
    /// @param pos Position du bouton
    /// @param size Taille du bouton
    /// @param color Couleur du bouton
    /// @param hoverColor Couleur du bouton lorsque survolé
    /// @param disableColor Couleur du bouton lorsque désactivé
    /// @param eventCode Code de l'événement que réalise le bouton lorsque cliqué
    Button(std::string text, Font* labelFont, SDL_Color labelColor, Vector2i pos, Vector2i size, SDL_Color color, SDL_Color hoverColor, unsigned int eventCode) : VisualComponent(pos, size) {
        Label* tempLabel = new Label(Vector2i(0, 0), labelFont, text, labelColor); 
        Vector2i labelRealSize = tempLabel->getSize();

        Vector2i labelPosition = MathUtils::getCenteredPosition(size, labelRealSize);
        this->label = new Label(Vector2i(pos.x + labelPosition.x, pos.y + labelPosition.y), labelFont, text, labelColor);
				this->label->setSize(labelRealSize);
        delete tempLabel;

        this->color = color;
        this->hoverColor = hoverColor;
        this->hover = false;
        this->eventCode = eventCode;
        this->enable = true;
    }

	/// @brief Destructeur
	~Button(){
		delete this->label;
	}

 	/// @brief Envoie le code de l'événement s'il y a un clic avec le bouton gauche de la souris
 	void notification() {
		if (this->enable) {
			switch(Event::getType()) {
				case SDL_MOUSEBUTTONDOWN: {
					SDL_Point mousePosition = Event::getMousePosition();
					SDL_Rect visualComponentRect = getRect();

					if(Event::getMouseButton() == SDL_BUTTON_LEFT && SDL_PointInRect(&mousePosition, &visualComponentRect))
						Event::push(eventCode);
				} break;

				case SDL_MOUSEMOTION: {
					SDL_Point mousePosition = Event::getMousePosition();
					SDL_Rect visualComponentRect = getRect();
					hover = SDL_PointInRect(&mousePosition, &visualComponentRect);
				} break;
			}
		}
	}

	void disableButton() {
		this->enable = false;
	}

	void enableButton() {
		this->enable = true;
	}


	/// @brief Afficher le bouton et son étiquette
	void render() {
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
			glColor4ubv(hover ? (unsigned char*)&hoverColor : (unsigned char*)&color);
			glVertex2i(this->getPos().x, this->getPos().y);
			glVertex2i(this->getPos().x + this->getSize().x, this->getPos().y);
			glVertex2i(this->getPos().x + this->getSize().x, this->getPos().y + this->getSize().y);
			glVertex2i(this->getPos().x, this->getPos().y + this->getSize().y);
		glEnd();

		glEnable(GL_TEXTURE_2D);

		this->label->render();
	}

	void updateLabelPosition(){
		Vector2i centered = MathUtils::getCenteredPosition(this->getSize(), this->label->getSize());
		this->label->setPosition(Vector2i(this->getPos().x + centered.x, this->getPos().y + centered.y));
	}
};