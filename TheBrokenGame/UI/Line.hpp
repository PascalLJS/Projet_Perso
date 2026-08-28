#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "VisualComponent.hpp"
#include "../Math/Vector2i.hpp"
#include "../Math/MathUtils.hpp"


/// @class Line
/// @brief Représente un ligne
class Line : public VisualComponent {
private:
  Vector2i startOfLine;
  Vector2i endOfLine;
  SDL_Color color;
  
public: 
  /// @brief Constructeur
  /// @param pos position de depart
  /// @param end postion de fin
  /// @param color couleur de la ligne
  Line(Vector2i pos, Vector2i end, SDL_Color color) : VisualComponent(pos){
    this->startOfLine = pos;
    this->endOfLine = end;
    this->color = color;
  }

  ~Line(){}

  Vector2i getPosStart(){
    return this->startOfLine;
  }

  Vector2i getPosEnd(){
    return this->endOfLine;
  }

  void setPosStart(Vector2i pos){
    this->startOfLine = pos;
  }

  void setPosEnd(Vector2i pos){
    this->endOfLine = pos;
  }

  void render() {

    glColor4ubv((unsigned char*)&color);

    glBegin(GL_LINES);

    glVertex2i(startOfLine.x, startOfLine.y);
    glVertex2i(endOfLine.x, endOfLine.y);

    glEnd();
  }
};