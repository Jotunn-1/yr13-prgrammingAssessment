#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include "texture.h"
#include "src/include/SDL2/SDL.h"

class Player
{
private:

  int m_velx, m_vely;
  int m_posx, m_posy;

public:

  static const int VEL = 1;

  void moveEvent( SDL_Event &event );
  void move();
  void tempRenderName( SDL_Renderer *renderer, Texture *player_texture);

};

#endif
