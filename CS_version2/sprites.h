//Class: sprites.h
#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include "texture.cpp"
#include "src/include/SDL2/SDL.h"

class Player
{
private:

  //Velocity declaration
  int m_velx, m_vely;

  int m_posx, m_posy;

  //Dimensions declaration
  int m_width = 20;
  int m_height = 40;

public:

  //Static variables are class specific not object specific
  static const int VEL = 10;

  void renderTest( SDL_Renderer *renderer, Texture *player_texture );

  //Player class method prototypes
  void moveEvent( SDL_Event& event );
  void move();

};

#endif
