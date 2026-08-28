#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../Events/Event.hpp"
#include "../DP/Observer.hpp"
#include "VisualComponent.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"
#include "Line.hpp"


/// @class Hitbox
class HitBox : Observer {
private:
	SDL_Color color = {255, 255, 255, 255}; ///< Couleur
  Vector2f pos; ///< Position en Float
  Vector2i size; ///< Taille de la boite de collision
	unsigned int eventType; ///< Type de la boite de collision

public:

	/// @brief Constructeur
	HitBox(Vector2f pos, Vector2i size, unsigned int eventType) {
		this->pos = pos;
		this->size = size;
		this->eventType = eventType;
	}

	/// @brief Default Constructeur
	HitBox(unsigned int eventType) {
		pos = Vector2f(0,0);
		size = Vector2i(0,0);
		this->eventType = eventType;
	}

	/// @brief Destructeur
	~HitBox(){}

	Vector2f getPos(){
		return this->pos;
	}

	Vector2i getSize() {
		return this->size;
	}

	void setPos(Vector2f newPos) {
		this->pos = newPos;
	}

	void setSize(Vector2i newSize) {
		this->size = newSize;
	}

	unsigned int getType() {
		return eventType;
	}

	void notification() {
		Event::push(eventType);
	}
	
	void render() {
		glDisable(GL_TEXTURE_2D);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_QUADS);
				glColor4ubv((unsigned char*)&color);
				glVertex2f(this->getPos().x, this->getPos().y);
				glVertex2f(this->getPos().x + this->getSize().x, this->getPos().y);
				glVertex2f(this->getPos().x + this->getSize().x, this->getPos().y + this->getSize().y);
				glVertex2f(this->getPos().x, this->getPos().y + this->getSize().y);
			glEnd();
		glEnable(GL_TEXTURE_2D);
	}
};