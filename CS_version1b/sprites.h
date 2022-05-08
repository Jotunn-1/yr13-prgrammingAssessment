//Class: sprites.h
#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include "src/include/SDL2/SDL.h"

class Player
{
private:

  //Velocity declaration
  int mVelX, mVelY;

  //Dimensions declaration
  int mWidth = 20;
  int mHeight = 40;


public:

  //Static variables are class specific not object specific
  static const int VEL = 10;

  SDL_Rect rect;

  //Player constructor
  PlayerConstruct();

  //Player class method prototypes
  void moveEvent( SDL_Event& event );
  void move();

};

#endif
