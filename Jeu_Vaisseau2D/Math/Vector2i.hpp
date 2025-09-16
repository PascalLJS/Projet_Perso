#pragma once
#include <iostream>
#include <cmath>


/// @file Vector2i.h
/// @brief Classe dérivée représentant un vecteur de deux composantes de type int.
/// @authors Carolanne St-André

/// @class Vector2i
/// @brief Représente un vecteur de deux composantes de type int.
class Vector2i {
public:
    int x; ///< Composante x du vecteur.
    int y; ///< Composante y du vecteur.

    /// @brief Constructeur pour initialiser les composantes du vecteur 2D.
    /// @param x Composante x.
    /// @param y Composante y.
    Vector2i(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    /// @brief Calcule la norme du vecteur 2D.
    /// @return La norme du vecteur.
    float getNorm() {
        return std::sqrt(x * x + y * y);
    }

    /// @brief Somme de deux vecteurs 2D.
    /// @param other Le vecteur à ajouter.
    /// @return Un vecteur résultant de la somme.
    Vector2i operator+(Vector2i& other) {
        return Vector2i(x + other.x, y + other.y);
    }

    /// @brief Différence de deux vecteurs 2D.
    /// @param other Le vecteur à soustraire.
    /// @return Un vecteur résultant de la différence.
    Vector2i operator-(Vector2i& other) {
        return Vector2i(x - other.x, y - other.y);
    }
};