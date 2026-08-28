#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "AnimatedSprite.hpp"
#include "../Events/Event.hpp"
#include "../Assets/Texture.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/Vector2f.hpp"
#include "../Math/MathUtils.hpp"
#include "../DP/ArrayStack.hpp"

/// @brief Père-Noel
class Santa : public AnimatedSprite {
private:
  Texture* texture;
  Vector2i size;
  ArrayStack<Direction> arrayStack;
  float frameX;
  float frameY;
  
public:

  /// @brief Centre la HitBox avec le Père-Noel
  void initializeHitBox() {
    this->hitBox->setPos(Vector2f(getCenter().x - 22, getCenter().y - 40));
    this->hitBox->setSize(Vector2i(40,78));
  }

  void initiateSpriteCoords() {
    int columns = texture->getWidth() / size.x;
    int rows = texture->getHeight() / size.y;
    this->frameX = 1.0f / columns;
    this->frameY = 1.0f / rows;
  }

  /// @brief Constructeur
  /// @param text Texture du Père-Noel
  /// @param pos Position en Float du Père-Noel
  /// @param size Taille du Père-Noel
  /// @param hitBox HitBox associé au Père-Noel
  Santa(Texture* text, Vector2f pos, Vector2i size, HitBox* hitBox) : AnimatedSprite(text, pos, size, hitBox), arrayStack(4) {
    this->texture = text;
    this->size = size;
    this->currentFrame = 0;
    this->animationTimer = 0.0f;
    this->frameDuration =0.10f;
    this->moving = false;
    initializeHitBox();
    initiateSpriteCoords();
  }

  ~Santa(){}

  /// @brief Remet l'animation à sa position Initiale
  void resetAnimation() {
    this->currentFrame = 0;
    this->animationTimer = 0.0f;
    this->animationIndex = 0;
  }

  /// @brief Calcule l'image à mettre pour le rendu
  /// @param deltaTime 
  void calculateFrame(double deltaTime) {
    animationTimer += deltaTime;
    int frameLoop[] = {1, 2, 1};
    if(animationTimer >= frameDuration) {
      animationTimer -= frameDuration;
      this->currentFrame = frameLoop[animationIndex];
      animationIndex = (animationIndex + 1) % 3;
    }
  }

  void moveUp(double deltaTime) {
    this->direction = Direction::Up;
    calculateFrame(deltaTime);
    this->pos.y -= speed * deltaTime;
  }

  void moveRight(double deltaTime) {
    this->direction = Direction::Right;
    calculateFrame(deltaTime);
    this->pos.x += speed * deltaTime;
  }

  void moveLeft(double deltaTime) {
    this->direction = Direction::Left;
    calculateFrame(deltaTime);
    this->pos.x -= speed * deltaTime;
  }

  void moveDown(double deltaTime) {
    this->direction = Direction::Down;
    calculateFrame(deltaTime);
    this->pos.y += speed * deltaTime;
  }

  /// @brief Gère la Direction du Père-Noel
  /// @param deltaTime
  void handleMovement(double deltaTime) {
    if(arrayStack.top() == Direction::Up)
      moveUp(deltaTime);
    if(arrayStack.top() == Direction::Down)
      moveDown(deltaTime);
    if(arrayStack.top() == Direction::Left)
      moveLeft(deltaTime);
    if(arrayStack.top() == Direction::Right)
      moveRight(deltaTime);
  }

  void reposition(Vector2f penetration) {
    if(arrayStack.top() == Direction::Up)
      this->pos.y -= penetration.y;
    else if(arrayStack.top() == Direction::Down)
      this->pos.y += penetration.y;
    else if(arrayStack.top() == Direction::Left)
      this->pos.x -= penetration.x;
    else if(arrayStack.top() == Direction::Right)
      this->pos += penetration.x;

    updateHitBox();
  }

  /// @brief Repositione la Hitbox avec la position du Père-Noel
  void updateHitBox() {
    hitBox->setPos(this->getPos() + Vector2f(getCenter().x - 22, getCenter().y - 40));
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
    // Up
    if (Event::isKeyDown(SDLK_w))
      arrayStack.push(Direction::Up);
    else
      arrayStack.removeValue(Direction::Up);
    // Right
    if (Event::isKeyDown(SDLK_d))
      arrayStack.push(Direction::Right);
    else
      arrayStack.removeValue(Direction::Right);
    // Left
    if (Event::isKeyDown(SDLK_a))
      arrayStack.push(Direction::Left);
    else
      arrayStack.removeValue(Direction::Left);
    // Down
    if (Event::isKeyDown(SDLK_s))
      arrayStack.push(Direction::Down);
    else
      arrayStack.removeValue(Direction::Down);


    if (arrayStack.isEmpty()) {
      resetAnimation();
    } else {
        handleMovement(deltaTime);
        updateHitBox();
    }
  }
};
