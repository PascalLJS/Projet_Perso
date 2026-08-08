#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "VisualComponent.hpp"
#include "../Assets/Texture.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/Vector2f.hpp"
#include "../Math/MathUtils.hpp"
#include "Line.hpp"

enum class Direction {
  Down = 0,
  Right,
  Left,
  Up
};

class AnimatedSprite{
private:
  Texture* texture;
  Vector2i size;
  Vector2f pos;
  int currentFrame; // 0,1,2
  Direction direction;
  float animationTimer;
  float frameDuration;
  int animationIndex = 0;
  int speed = 150;
  bool moving;
  
public: 
  /// @brief Constructeur
  /// @param pos position de depart
  AnimatedSprite(Texture* text, Vector2f pos, Vector2i size) {
    this->texture = text;
    this->pos = pos;
    this->size = size;
    this->currentFrame = 0;
    this->direction = Direction::Down;
    this->animationTimer = 0.0f;
    this->frameDuration =0.10f;
    this->moving = false;
  }

  ~AnimatedSprite() {}

  void resetAnimation() {
    this->currentFrame = 0;
    this->animationTimer = 0.0f;
    this->animationIndex = 0;
  }

  void calculateFrame(double deltaTime) {
    animationTimer += deltaTime;
    int frameLoop[] = {1, 2, 1};
    if(animationTimer >= frameDuration) {
      animationTimer -= frameDuration;
      this->currentFrame = frameLoop[animationIndex];
      animationIndex = (animationIndex + 1) % 3;
    }
  }

  void moveUp(double deltaTime){
    this->direction = Direction::Up;
    calculateFrame(deltaTime);
    this->pos.y -= speed * deltaTime;
  }

  void moveRight(double deltaTime){
    this->direction = Direction::Right;
    calculateFrame(deltaTime);
    this->pos.x += speed * deltaTime;
  }

  void moveLeft(double deltaTime){
    this->direction = Direction::Left;
    calculateFrame(deltaTime);
    this->pos.x -= speed * deltaTime;
  }

  void moveDown(double deltaTime){
    this->direction = Direction::Down;
    calculateFrame(deltaTime);
    this->pos.y += speed * deltaTime;
  }

  void render() {
    if (texture) {
      texture->bind();
      // Size of one sprite in UV coordinates
      int columns = texture->getWidth() / size.x;
      int rows = texture->getHeight() / size.y;

      float frameU = 1.0f / columns;
      float frameV = 1.0f / rows;

      float u0 = currentFrame * frameU;
      float v0 = static_cast<int>(direction) * frameV;

      float u1 = u0 + frameU;
      float v1 = v0 + frameV;

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
    if(Event::isKeyDown(SDLK_w))
      moveUp(deltaTime);
    else if(Event::isKeyDown(SDLK_d))
      moveRight(deltaTime);
    else if(Event::isKeyDown(SDLK_a))
      moveLeft(deltaTime);
    else if(Event::isKeyDown(SDLK_s))
      moveDown(deltaTime);
    else
    resetAnimation();
  }
};