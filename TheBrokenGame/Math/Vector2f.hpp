#pragma once
#include <iostream>
#include <cmath>


class Vector2f
{
public:
    float x;
    float y;

    Vector2f(float x = 0, float y = 0){
      this->x = x;
      this->y = y;
    }

    Vector2f& operator+=(const Vector2f& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /// @brief Différence de deux vecteurs 2D.
    /// @param other Le vecteur à soustraire.
    /// @return Un vecteur résultant de la différence.
    Vector2f operator-=(Vector2f& other) {
        return Vector2f(x - other.x, y - other.y);
    }
};