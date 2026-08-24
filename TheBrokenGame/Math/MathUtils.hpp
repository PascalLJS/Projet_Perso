#pragma once

#include <iostream>
#include <cmath>
#include "Vector2i.hpp"

#define PI 3.14159265358979323846

/// @class MathUtils
/// @brief Fournit des utilitaires mathématiques.
class MathUtils {
public:
	/// @brief Convertit des degrés en radians.
	/// @param degrees La valeur en degrés.
	/// @return La valeur convertie en radians.
	static double degreesToRadians(double degrees) {
		return degrees * (PI / 180.0);
	}

	/// @brief Convertit des radians en degrés.
	/// @param radians La valeur en radians.
	/// @return La valeur convertie en degrés.
	static double radiansToDegrees(double radians) {
		return radians * (180.0 / PI);
	}

	/// @brief Calcule la position centrée d'un composant sur une surface donnée.
	/// @param surfaceWidth Largeur de la surface sur laquelle centrer le composant.
	/// @param surfaceHeight Hauteur de la surface sur laquelle centrer le composant.
	/// @param componentWidth Largeur du composant à centrer.
	/// @param componentHeight Hauteur du composant à centrer.
	/// @return Un objet Vector2i représentant la position centrée du composant.
	static Vector2i getCenteredPosition(unsigned int surfaceWidth, unsigned int surfaceHeight, unsigned int componentWidth, unsigned int componentHeight) {
    return Vector2i(surfaceWidth / 2 - componentWidth / 2, surfaceHeight / 2 - componentHeight / 2);
	}

	/// @brief Calcule la position centrée d'un composant sur une surface donnée.
	/// @param surfaceWidth Largeur de la surface sur laquelle centrer le composant.
	/// @param componentWidth Largeur du composant à centrer.
	/// @return La valeur X représentant la position centrée du composant.
	static int getCenteredPositionX(unsigned int surfaceWidth, unsigned int componentWidth) {
    return int(surfaceWidth / 2 - componentWidth / 2);
	}

	/// @brief Calcule la position centrée d'un composant sur une surface donnée.
	/// @param surfaceHeight Hauteur de la surface sur laquelle centrer le composant.
	/// @param componentHeight Hauteur du composant à centrer.
	/// @return La valeur Y représentant la position centrée du composant.
	static int getCenteredPositionY(unsigned int surfaceHeight, unsigned int componentHeight) {
    return int(surfaceHeight / 2 - componentHeight / 2);
	}

	static Vector2i getCenteredPoint(Vector2i componentSize) {
		return Vector2i(componentSize.x / 2, componentSize.y / 2);
	}

	/// @brief Calcule la position centrée en X d'un composant sur une surface donnée.
	/// @param surfaceWidth Largeur de la surface sur laquelle centrer le composant.
	/// @param componentWidth Largeur du composant à centrer.
	/// @return Un objet Vector2i représentant la position centrée du composant.
	static Vector2i getCenteredPosition(unsigned int surfaceWidth, unsigned int componentWidth, unsigned int y) {
    return Vector2i(surfaceWidth / 2 - componentWidth / 2, y);
	}
};