#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "AnimatedSprite.hpp"
#include "../Assets/Texture.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/Vector2f.hpp"
#include "../Math/MathUtils.hpp"

/// @brief Cadeau
class Present : public AnimatedSprite {
private:
  float frameX;
  float frameY;
  
public:

  /// @brief Centre la HitBox avec le Cadeau
  void initializeHitBox() {
    this->hitBox->setPos(Vector2f((getPos().x + (getCenter().x - 10)), (getPos().y + (getCenter().y - 10))));
    this->hitBox->setSize(Vector2i(20,20));
  }

  void initiateSpriteCoords() {
    int columns = texture->getWidth() / size.x;
    int rows = texture->getHeight() / size.y;
    this->frameX = 1.0f / columns;
    this->frameY = 1.0f / rows;
  }

  /// @brief Constructeur
  /// @param text Texture du Cadeau
  /// @param pos Position en Float du Cadeau
  /// @param size Taille du Cadeau
  /// @param hitBox HitBox associé au Cadeau
  Present(Texture* text, Vector2f pos, Vector2i size, unsigned int direction, int speed, HitBox *hitBox) : AnimatedSprite(text, pos, size, direction, speed, hitBox) {
    initializeHitBox();
    initiateSpriteCoords();
  }

  ~Present(){}

  /// @brief Remet l'animation à sa position Initiale
  void resetAnimation() {
    this->currentFrame = 0;
    this->animationTimer = 0.0f;
    this->animationIndex = 0;
  }

  /// @brief Calcule l'image à mettre pour le rendu
  /// @param deltaTime 
  void calculateFrame(double deltaTime) {
    int frameLoop[4] = {0, 1, 2, 3};
    animationTimer += deltaTime;
    if(animationTimer >= frameDuration) {
      animationTimer -= frameDuration;
      this->currentFrame = frameLoop[animationIndex];
      animationIndex = (animationIndex + 1) % 3;
    }
  }

  void moveRight(double deltaTime) {
    calculateFrame(deltaTime);
    this->pos.x += speed * deltaTime;
  }

  void moveLeft(double deltaTime) {
    calculateFrame(deltaTime);
    this->pos.x -= speed * deltaTime;
  }

  void reposition(Vector2f penetration) {}

  /// @brief Repositione la Hitbox avec la position du Cadeau
  void updateHitBox() {
    this->hitBox->setPos(Vector2f((getPos().x + (getCenter().x - 10)), (getPos().y + (getCenter().y - 10))));
  }

  void render() {
    if (texture) {
      texture->bind();
      float u0 = currentFrame * frameX;
      float v0 = static_cast<int>(direction) * frameY;

      float u1 = u0 + frameX;
      float v1 = v0 + frameY;

      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
          glTexCoord2f(u0, v0);
          glVertex2f(pos.x, pos.y);
          glTexCoord2f(u1, v0);
          glVertex2f(pos.x + size.x, pos.y);
          glTexCoord2f(u1, v1);
          glVertex2f(pos.x + size.x, pos.y + size.y);
          glTexCoord2f(u0, v1);
          glVertex2f(pos.x, pos.y + size.y);
      glEnd();
      glDisable(GL_TEXTURE_2D);
    }
  }

  void update(double deltaTime) {
    if(this->pos.x < 30 || this->pos.x > 1135)
      resetPosition();
    else {
      if(this->direction == Direction::Left)
        moveLeft(deltaTime);
      else
        moveRight(deltaTime);
    }

    updateHitBox();
  }
};