#pragma once

#include "VisualComponent.hpp"
#include "../Math/Vector2i.hpp"
#include <map>

/// @class Grid
/// @brief Contient des VisualComponents pour mieux les placer
class Grid : public VisualComponent {
private:
  Vector2i size; ///< Size du grid
  Vector2i position; ///< Position du grid
  int nbComponents; ///< Index pour la position des elements dans la map
  int column; ///< Nombre de colonne
  int innerPadding; ///< Padding entre les elements
  int padding; ///< Padding entre le grid et les elements
  std::map<int, VisualComponent*> grid; ///< Contient tous les elements inclu dans le grid

public:
  Grid(int column, Vector2i size, Vector2i pos, int innerPadding, int padding) : VisualComponent(size) {
    column > 10 || column < 1 ? this->column = 1 : this->column = column; 
    nbComponents = 0;
    this->innerPadding = innerPadding;
    this->padding = padding;
  }

  /// @brief Reajuste le size du grid apres ajout d'un element
  void readjustSize(VisualComponent* visualComponent) {
    if(column > 1 && nbComponents % column != 0) {

    } else { 
      
    }
  }

  /// @brief Ajoute un visualComponent dans le grid
  /// @param visualComponent 
  void addItem(VisualComponent* visualComponent) {
    grid[nbComponents++] = visualComponent;
    readjustSize(visualComponent);
  }

  void render() override { 
    for (auto it : grid)
			it.second->render();
  }
};
