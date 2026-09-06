#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../Assets/Texture.hpp"
#include "../CollisionDetection/HitBox.hpp"
#include "../CollisionDetection/CollisionManager.hpp"
#include "../Math/MathUtils.hpp"


class DeathRock {
  private:
    Vector2f pos;
    Vector2i size;
    Texture *texture;
    HitBox *hitBox;
    int speed = 100;

  public:

  DeathRock(Vector2f pos, Vector2i size, Texture *texture, HitBox *hitbox) {
    this->pos = pos;
    this->size = size;
    this->texture = texture;
    this->hitBox = hitbox;
  }

  ~DeathRock() {}

  void updateHitbox() {
    this->hitBox->setPos(this->pos + Vector2f(45, 45));
  }

  void updateSizeHitbox() {
    this->hitBox->setSize(Vector2i(40, 25));
  }

  void setPosition(Vector2f targetPos) {
    this->pos = Vector2f(targetPos.x - 40, 0.0);
    updateSizeHitbox();
  }

  void render() {
    if (texture) {
      texture->bind();
      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);glVertex2f(pos.x, pos.y);
				glTexCoord2f(1,0);glVertex2f(pos.x + size.x, pos.y);
				glTexCoord2f(1,1);glVertex2f(pos.x + size.x, pos.y + size.y);
				glTexCoord2f(0,1);glVertex2f(pos.x, pos.y + size.y);
      glEnd();
      glDisable(GL_TEXTURE_2D);
    }
  }

  void update(double deltaTime) {
    this->pos.y += speed * deltaTime;
    updateHitbox();
  }
};