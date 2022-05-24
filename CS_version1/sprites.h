#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include "src/include/SDL2/SDL.h"

class Player
{
private:

  int mVelX, mVelY;

  int mWidth = 20;
  int mHeight = 40;


public:
  static const int VEL = 1;

    SDL_Rect playerPos;

  PlayerConstruct();
  void moveEvent( SDL_Event& event );
  void move();

};

#endif
