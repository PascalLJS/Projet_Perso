#pragma once

#include <string>
#include <SDL2/SDL_opengl.h>
#include <list>

#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"
#include "VisualComponent.hpp"
#include "Label.hpp"

enum CenteredType {
  LEFT = 0,
  CENTERED,
  RIGHT
};

class LabelGrid : public VisualComponent {
  private:
    std::list<Label*> labelsList;
    unsigned int centeredType = LEFT;
    bool showTime = false;


  /// @brief Calcule la position de chaque label selon le type de Centralisation
  void recalculatePosition(Vector2i biggestSize) {
    int yOffset = labelsList.front()->getSize().y;
    int count = 0;
    switch (centeredType) {
      case CENTERED:
          
        break;
      case RIGHT:
      
        break;
      case LEFT:
        for(auto it = labelsList.begin(); it != labelsList.end(); ++it) {
          (*it)->setPosition(Vector2i(this->getPos().x, this->getPos().y + yOffset * count));
          count++;
        }
        break;
    }
  }

  /// @brief Calcule la grosseur de la grille
  void recalculateSizeAndPosition() {
    if(!labelsList.empty()) { 
      auto it = labelsList.begin();
      Vector2i newSize = (*it)->getSize();
      for (++it; it != labelsList.end(); ++it) {
        if (newSize.x < (*it)->getSize().x)
          newSize.x = (*it)->getSize().x;
        newSize.y += (*it)->getSize().y;
      }
      this->setSize(newSize);
      recalculatePosition(newSize);
    } else
      this->setSize(Vector2i(0,0));
  }

  public:

  /// @brief Grille de Label
  /// @param pos Vector représentant la position 
  /// @param size Vector représentant la grosseur
  /// @param centeredType Type de centralisation | 0 pour Gauche, 1 pour Centrer et 2 pour Droite
  LabelGrid(Vector2i pos, Vector2i size, unsigned int centeredType) : VisualComponent(pos, size) {
    this->centeredType = centeredType;
  }

  ~LabelGrid() {
    labelsList.clear();
  }

  void removeLabel(Label* label) {
    labelsList.remove(label);
    if(!labelsList.empty())
      recalculateSizeAndPosition();
  }

  void resetPosition() {
    recalculatePosition(this->size);
  }

  void addLabel(Label *label) {
      labelsList.push_back(label);
      recalculateSizeAndPosition();
  }

  /// @brief Set showTime bool to its opposite
  void setVisible() {
    showTime = true;
  }

  void setInvisible() {
    showTime = false;
  }

  void clear() {
    labelsList.clear();
  }

  void render() {
    if(showTime)
      for(auto it : labelsList)
        it->render();
  }
};