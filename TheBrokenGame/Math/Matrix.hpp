#pragma once
#include "Vector2i.hpp"
#include <cmath>

#define M11 0
#define M12 1
#define M13 2
#define M14 3
#define M21 4
#define M22 5
#define M23 6
#define M24 7
#define M31 8
#define M32 9
#define M33 10
#define M34 11
#define M41 12
#define M42 13
#define M43 14
#define M44 15

#define PI 3.14159265358979323846

/// @class Matrix
/// @brief Permet de gérer les matrices. Obtention de la matrice de transformation par l'opérateur *.
class Matrix {
private:
	float matrix[16] {}; ///< Matrice de transformation

public:
	/// @brief Charge la matrice orthographique
	/// @param width Largeur, en pixels, du moteur de rendu
	/// @param height Hauteur, en pixels, du moteur de rendu
	void loadProjection(int width, int height) {
		matrix[0] = 2.0 / float(width); matrix[1] = 0.0; matrix[2] = 0.0; matrix[3] = 0.0;
		matrix[4] = 0.0; matrix[5] = 2.0 / float(-height); matrix[6] = 0.0; matrix[7] = 0.0;
		matrix[8] = 0.0; matrix[9] = 0.0; matrix[10] = 1.0; matrix[11] = 0.0;
		matrix[12] = -1.0; matrix[13] = 1.0; matrix[14] = 0.0; matrix[15] = 1.0;
	}

	/// @brief Obtention de la matrice interne
	operator float*() {
		return matrix;
	}
};