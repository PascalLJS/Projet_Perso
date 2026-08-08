#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "VisualComponent.hpp"
#include "../Assets/Texture.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"
#include "Line.hpp"

enum class Direction
{
  Down = 0,
  Right,
  Left,
  Up
};

class AnimatedSprite : public VisualComponent {
private:
  Texture* texture;
  Vector2i size;
  int currentFrame; // 0,1,2
  Direction direction;
  float animationTimer;
  float frameDuration;
  bool moving;
  
public: 
  /// @brief Constructeur
  /// @param pos position de depart
  AnimatedSprite(Texture* text, Vector2i pos, Vector2i size) : VisualComponent(pos){
    this->texture = text;
    this->pos = pos;
    this->size = size;
    this->currentFrame = 0;
    this->direction = Direction::Down;
    this->animationTimer = 0.0f;
    this->frameDuration =0.15f;
    this->moving = false;
  }

  ~AnimatedSprite(){}


  void render() override {
    if (texture) {
      texture->bind();
      int column = currentFrame;
      int row = static_cast<int>(direction);
      // Size of one sprite in UV coordinates
      float frameU = 1.0f / 3.0f; // 3 columns
      float frameV = 1.0f / 4.0f; // 4 rows

      float u0 = column * frameU;
      float v0 = row * frameV;

      float u1 = u0 + frameU;
      float v1 = v0 + frameV;

      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
          glTexCoord2f(u0, v0);
          glVertex2i(pos.x, pos.y);
          glTexCoord2f(u1, v0);
          glVertex2i(pos.x + size.x, pos.y);
          glTexCoord2f(u1, v1);
          glVertex2i(pos.x + size.x, pos.y + size.y);
          glTexCoord2f(u0, v1);
          glVertex2i(pos.x, pos.y + size.y);
      glEnd();
      glDisable(GL_TEXTURE_2D);

    }
  }
};