#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../Assets/Texture.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/Vector2f.hpp"
#include "../Math/MathUtils.hpp"
#include "VisualComponent.hpp"
#include "../CollisionDetection/HitBox.hpp"

/// @brief Image animé
class AnimatedSprite : public VisualComponent {
protected:
  Texture* texture;
  Vector2f initialPos;
  int currentFrame;
  float animationTimer;
  float frameDuration;
  int animationIndex = 0;
  int speed = 150;
  bool moving;
  HitBox* hitBox;
  
public: 
  /// @brief Constructeur
  /// @param text
  /// @param pos
  /// @param size
  AnimatedSprite(Texture* text, Vector2f posF, Vector2i size, HitBox *hitbox) : VisualComponent(posF, size) {
    this->texture = text;
    this->currentFrame = 0;
    this->initialPos = posF;
    this->animationTimer = 0.0f;
    this->frameDuration =0.10f;
    this->moving = false;
    this->hitBox = hitbox;
  }

  virtual ~AnimatedSprite() {}

  void resetAnimation() {
    this->currentFrame = 0;
    this->animationTimer = 0.0f;
    this->animationIndex = 0;
  }

  void resetPosition() {
    this->posF = initialPos;
    this->hitBox->setPos(posF);
  }

  Vector2i getCenter() { 
    return MathUtils::getCenteredPoint(this->size);
  }

  virtual void calculateFrame(double deltaTime) = 0;

  virtual void render() = 0;

  virtual void update(double deltaTime) = 0;
};
