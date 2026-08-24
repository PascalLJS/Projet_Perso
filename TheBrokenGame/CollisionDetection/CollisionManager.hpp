#pragma once

#include <list>
#include <map>
#include <string>
#include "HitBox.hpp"

/// @brief 
class CollisionManager {
private:
  list<HitBox*> hitBoxes;
public:
  CollisionManager() {}

  ~CollisionManager() {
    
  }
  
  void checkCollision(HitBox *hitbox, HitBox *otherHitbox) {

  }

  void addHitBox(HitBox *hitbox) {
    hitBoxes.push_back(hitbox);
  }

  void removeHitBox(HitBox *hitbox) {
    hitBoxes.remove(hitbox);
  }
};