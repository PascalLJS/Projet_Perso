#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../Assets/Texture.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/Vector2f.hpp"
#include "../Math/MathUtils.hpp"
#include "VisualComponent.hpp"
#include "../CollisionDetection/HitBox.hpp"

enum Direction {
  Down = 0,
  Right,
  Left,
  Up
};

/// @brief Image animé
class AnimatedSprite {
protected:
  Texture* texture;
  Vector2f pos;
  Vector2f initialPos;
  Vector2i size;
  unsigned int direction;
  int currentFrame;
  float animationTimer;
  float frameDuration;
  int animationIndex = 0;
  int speed = 150;
  bool moving;
  HitBox* hitBox;
  
public: 
  
  AnimatedSprite(Texture* text, Vector2f pos, Vector2i size, HitBox *hitbox) {
    this->texture = text;
    this->currentFrame = 0;
    this->pos = pos;
    this->initialPos = pos;
    this->size = size;
    this->direction = Direction::Down;
    this->animationTimer = 0.0f;
    this->frameDuration =0.10f;
    this->moving = false;
    this->hitBox = hitbox;
  }

  AnimatedSprite(Texture* text, Vector2f pos, Vector2i size, unsigned int direction, int speed, HitBox *hitbox) {
    this->texture = text;
    this->currentFrame = 0;
    this->pos = pos;
    this->initialPos = pos;
    this->size = size;
    this->speed = speed;
    this->direction = direction;
    this->animationTimer = 0.0f;
    this->frameDuration =0.10f;
    this->moving = false;
    this->hitBox = hitbox;
  }

  virtual ~AnimatedSprite() {}

  Vector2f getPos() {
    return this->pos;
  }

  void resetAnimation() {
    this->currentFrame = 0;
    this->animationTimer = 0.0f;
    this->animationIndex = 0;
  }

  void resetPosition() {
    this->pos = initialPos;
    this->hitBox->setPos(pos);
  }

  unsigned int getDirection() {
    return direction;
  }

  Vector2i getCenter() { 
    return MathUtils::getCenteredPoint(this->size);
  }

  virtual void reposition(Vector2f penetration) = 0;

  virtual void calculateFrame(double deltaTime) = 0;

  virtual void render() = 0;

  virtual void update(double deltaTime) = 0;
};
