//Johnathan Regha-Dodge: CS_version1/load_media.h
//Load media class

// Makes sure nothing is imported multiple times
#ifndef LOAD_MEDIA_H
#define LOAD_MEDIA_H

// Imports
#include <iostream>
#include "src/include/SDL2/SDL.h"

class LoadMedia
{
public:

  //SDL_Surface declarations
  SDL_Surface *m_player;
  SDL_Surface *m_background;

  //Class method loadMedia prototype
  bool loadMedia();

};

#endif
