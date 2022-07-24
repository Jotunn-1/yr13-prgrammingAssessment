//Johnathan Regha-Dodge: CS_version2/sprites.h
//Sprite class

#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include "texture.h"
#include "screen.h"
#include "src/include/SDL2/SDL.h"

class Player
{
private:

  float m_velx, m_vely;
  float m_posx, m_posy;

  int m_width, m_height;

public:

  static const int VEL = 640;

  void getDimensions( Texture *player_texture );
  void moveEvent( SDL_Event &event );
  void move( float *time_step, Screen *screen );
  void tempRenderName( SDL_Renderer *renderer, Texture *player_texture);

};

#endif
