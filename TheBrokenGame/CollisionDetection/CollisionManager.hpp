#pragma once

#include <list>
#include "HitBox.hpp"

enum CollisionDirection {
  CDown = 0,
  CRight,
  CLeft,
  CUp
};

/// @brief 
class CollisionManager {
private:
  Vector2f penetration;

  void calculateCollisionPenetration(HitBox *player, HitBox *obstacle, unsigned int direction) {
    if(direction == CollisionDirection::CUp)
      penetration = Vector2f(0.0, player->getPos().y - (obstacle->getPos().y + obstacle->getSize().y));
    else if(direction == CollisionDirection::CLeft)
      penetration = Vector2f(player->getPos().x - (obstacle->getPos().x + obstacle->getSize().x), 0.0);
    else if (direction == CollisionDirection::CRight)
      penetration = Vector2f(obstacle->getPos().x - (player->getPos().x + player->getSize().x), 0.0);
    else if (direction == CollisionDirection::CDown)
      penetration = Vector2f(0.0, obstacle->getPos().y - (player->getPos().y + player->getSize().y));
  }

  void calculateDepthOutOfMap(HitBox *hitbox, Vector2i mapSize, unsigned int direction) {
    if(direction == CollisionDirection::CUp)
      penetration = Vector2f(0.0, hitbox->getPos().y);
    else if(direction == CollisionDirection::CLeft)
      penetration = Vector2f(hitbox->getPos().x, 0.0);
    else if (direction == CollisionDirection::CRight)
      penetration = Vector2f(mapSize.x - (hitbox->getPos().x + hitbox->getSize().x), 0.0);
    else if(direction == CollisionDirection::CDown)
      penetration = Vector2f(0.0, mapSize.y - (hitbox->getPos().y + hitbox->getSize().y));

    hitbox->notification();
  }

public:
  CollisionManager() {}

  ~CollisionManager() {}
  
  bool checkCollision(HitBox *player, HitBox *obstacle, unsigned int direction) {
    if(player->getPos().x < obstacle->getPos().x + obstacle->getSize().x &&
    player->getPos().x + player->getSize().x > obstacle->getPos().x &&
    player->getPos().y < obstacle->getPos().y + obstacle->getSize().y &&
    player->getPos().y + player->getSize().y > obstacle->getPos().y) {
      if(obstacle->getType() == SANTA_OUT_OF_BOUND)
        calculateCollisionPenetration(player, obstacle, direction);
      obstacle->notification();
      return true;
    }
    return false;
  }

  bool checkOutOfMap(HitBox *santaHitbox, Vector2i mapSize, unsigned int direction) {
    if(santaHitbox->getPos().x < 0.0 || (santaHitbox->getPos().x + santaHitbox->getSize().x) > mapSize.x || santaHitbox->getPos().y < 0.0 || (santaHitbox->getPos().y + santaHitbox->getSize().y) > mapSize.y) {
      calculateDepthOutOfMap(santaHitbox, mapSize, direction);
      return true;
    }
    return false;
  }

  Vector2f getPenetration() {
    return this->penetration;
  }
};