//Class: load_media.h
#ifndef LOAD_MEDIA_H
#define LOAD_MEDIA_H

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
