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

class LabelGrid : VisualComponent {
  private:
    std::list<Label*> labelsList;
    unsigned int centeredType = CENTERED;


  /// @brief Calcule la position de chaque label selon le type de Centralisation
  void recalculatePosition() {

  }

  /// @brief Calcule la grosseur de la grille
  void recalculateSizeAndPosition() {
    if(!labelsList.empty()) { 
      Vector2i newSize = labelsList.front()->getSize();
      for(auto it = ++labelsList.front(); it != labelsList.back(); ++it) {
        if(newSize.x < it->getSize().x)
          newSize.x = it->getSize().x;
        newSize.y += it->getSize().y;
      }
      this->setSize(newSize);
      recalculatePosition();
    }
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

  ~LabelGrid() {}

  void removeLabel(Label* label) {
    labelsList.remove(label);
    recalculateSizeAndPosition();
  }

  void addLabel(Label *label) {
    labelsList.push_back(label);
    recalculateSizeAndPosition();
  }

  void render() {
    for(auto it : labelsList)
      it->render();
  }
};