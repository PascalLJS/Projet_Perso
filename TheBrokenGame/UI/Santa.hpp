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


enum class Direction {
  Down = 0,
  Right,
  Left,
  Up
};

/// @brief Père-Noel
class Santa : public AnimatedSprite {
private:
  Texture* texture;
  Vector2i size;
  Vector2f lastPos;
  int currentFrame;
  Direction direction;
  ArrayStack<Direction> arrayStack;
  float animationTimer;
  float frameDuration;
  int animationIndex = 0;
  int speed = 150;
  float frameX;
  float frameY;
  bool moving;
  
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
    this->lastPos = pos;
    this->size = size;
    this->currentFrame = 0;
    this->direction = Direction::Down;
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
    this->posF.y -= speed * deltaTime;
  }

  void moveRight(double deltaTime) {
    this->direction = Direction::Right;
    calculateFrame(deltaTime);
    this->posF.x += speed * deltaTime;
  }

  void moveLeft(double deltaTime) {
    this->direction = Direction::Left;
    calculateFrame(deltaTime);
    this->posF.x -= speed * deltaTime;
  }

  void moveDown(double deltaTime) {
    this->direction = Direction::Down;
    calculateFrame(deltaTime);
    this->posF.y += speed * deltaTime;
  }

  bool isOutOfMapNorth() {
    if(this->hitBox->getPos().y < 0.0) {
      updateHitBox(Vector2f(this->posF.x + getCenter().x - 22, 0.0));
      return true;
    }
    return false;
  }

  bool isOutOfMapEast() {
    if(this->hitBox->getPos().x > 1280 - hitBox->getSize().x) {
      updateHitBox(Vector2f(1280 - hitBox->getSize().x, this->posF.y + getCenter().y - 40));
      return true;
    }
    return false;
  }

  bool isOutOfMapWest() {
    if(this->hitBox->getPos().x < 0.0) {
      updateHitBox(Vector2f(0.0, this->posF.y + getCenter().y - 40));
      return true;
    }
    return false;
  }

  bool isOutOfMapSouth() {
    if(this->hitBox->getPos().y > (720 - hitBox->getSize().y)) {
      updateHitBox(Vector2f(this->posF.x + getCenter().x - 22, 720 - hitBox->getSize().y));
      return true;
    }
    return false;
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

  void repositionSantaInsideMap() {
    this->posF = lastPos;
  }

  void repositionSanta() {
  }

  void updateHitBox(Vector2f vector) {
    hitBox->setPos(vector);
  }

  /// @brief Repositione la Hitbox avec la position du Père-Noel
  void updateHitBox() {
    hitBox->setPos(this->getPosF() + Vector2f(getCenter().x - 22, getCenter().y - 40));
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
          glVertex2f(posF.x, posF.y);
          glTexCoord2f(u1, v0);
          glVertex2f(posF.x + size.x, posF.y);
          glTexCoord2f(u1, v1);
          glVertex2f(posF.x + size.x, posF.y + size.y);
          glTexCoord2f(u0, v1);
          glVertex2f(posF.x, posF.y + size.y);
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
      if(!isOutOfMapNorth() && !isOutOfMapEast() && !isOutOfMapWest() && !isOutOfMapSouth()) {
        this->lastPos = posF;
        handleMovement(deltaTime);
        updateHitBox();
      } else
        this->hitBox->notification();
    }
  }
};
