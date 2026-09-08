#pragma once

#include <string>
#include <SDL2/SDL_opengl.h>
#include <list>

#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"
#include "VisualComponent.hpp"
#include "Button.hpp"
#include "Alignments.hpp"

class ButtonGrid : public VisualComponent {
  private:
    std::list<Button*> buttonsList;
    int padding;
    int column;
    int row;
    bool buttonsEnable = true;

    void calculateSize() {
      this->size = Vector2i((buttonsList.front()->getSize().x * column) + (padding * (column - 1)), (buttonsList.front()->getSize().y * row) + (padding * (row - 1)));
    }

    void calculateButtonPosition() {
      const int btnW = buttonSize().x;
      const int btnH = buttonSize().y;

      int index = 0;
      for (auto it : buttonsList) {
          int col = index % column;
          int row = index / column;

          int x = pos.x + col * (btnW + padding);
          int y = pos.y + row * (btnH + padding);

          it->setPosition(Vector2i(x, y));
          it->updateLabelPosition();
          ++index;
      }
    }

  public:
  /// @brief Grille de Bouton
  /// @param pos Vector représentant la position 
  /// @param size Vector représentant la grosseur
  /// @param centeredType Type de centralisation | 0 pour Gauche, 1 pour Centrer et 2 pour Droite
  ButtonGrid(Vector2i pos, Vector2i size, int padding, int column, int row) : VisualComponent(pos, size) {
    this->padding = padding;
    this->column = column;
    this->row = row;
  }

  ~ButtonGrid() {  
    for(auto it : buttonsList)
      delete it;
    buttonsList.clear(); 
  }

  void removeButton(Button* button) {
    buttonsList.remove(button);
  }

  void disableButtons() {
    for(auto it : buttonsList)
      it->disableButton();
    this->buttonsEnable = false;
  }

  void enableButtons() {
    for(auto it : buttonsList)
      it->enableButton();
    this->buttonsEnable = true;
  }

  bool isButtonsEnable() {
    return this->buttonsEnable;
  }

  Vector2i buttonSize() {
    return buttonsList.front()->getSize();
  }

  std::list<Button*> getList() {
    return this->buttonsList;
  }

  void setPosition(Vector2i pos) {
    this->pos = pos;
    calculateButtonPosition();
  }

  void addButton(Button *button) {
    if(buttonsList.empty()) {
      buttonsList.push_back(button);
      calculateSize();
    }
    else
      buttonsList.push_back(button);
  }

  void render() {
    for(auto it : buttonsList)
      it->render();
  }
};