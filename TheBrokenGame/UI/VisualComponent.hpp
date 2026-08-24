#pragma once

#include <SDL2/SDL.h>

#include "../Math/Vector2i.hpp"
#include "../Math/Vector2f.hpp"

/// @class VisualComponent
/// @brief Classe commune pour les composents visuels
class VisualComponent {
protected:
	Vector2i pos; ///< position (en haut à gauche) du composant
	Vector2i size; ///< taille du composant
	Vector2f posF; ///< position en Float de composant

public:
	/// @brief Constructeur de composant
	/// @param pos La position (Vecteur2i)
	/// @param size La taille (Vecteur2i)
	VisualComponent(Vector2i pos, Vector2i size) {
		this->pos = pos;
		this->size = size;
		this->posF = Vector2f(0.0, 0.0);
	}

	/// @brief Constructeur de composant sans taille
	/// @param pos La position (Vecteur2i)
	VisualComponent(Vector2i pos) {
		this->pos = pos;
		this->size = Vector2i(0,0);
		this->posF = Vector2f(0.0, 0.0);
	}

	VisualComponent(Vector2f pos, Vector2i size) {
		this->posF = pos;
		this->size = size;
		this->pos = Vector2i(0,0);
	}

	virtual ~VisualComponent() {}

	/// @brief Obtient la position du composant
	/// @return Un vecteur de position
	Vector2i getPos() {
		return pos;
	}

	Vector2f getPosF() {
		return posF;
	}

	/// @brief Change la position du composant visuel
	/// @param position Vecteur de la nouvelle position
	void setPosition(Vector2i position){
		if(position.x < 0)
			position.x = 0;
		if(position.y < 0)
			position.y = 0;
		this->pos = position;
	}

	/// @brief Obtient la taille du composant
	/// @return Un vecteur de taille
	Vector2i getSize() {
		return size;
	}

	/// @brief Change la taille du visuel
	/// @param size Vecteur de la taille
	void setSize(Vector2i size) {
		this->size = size;
	}

	/// @brief Obtient le rectangle SDL du composant
	/// @return Un rectangle SDL contenant la position et la taille
	SDL_Rect getRect() {
		return {pos.x, pos.y, size.x, size.y};
	}

	/// @brief Méthode abstraite permettant le rendu visuel
	virtual void render() = 0;
};