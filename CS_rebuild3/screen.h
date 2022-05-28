#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include "texture.h"
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

class Screen
{

public:

  static const int SCREEN_WIDTH = 640;
  static const int SCREEN_HEIGHT = 480;

private:

  SDL_Window *m_window;

  SDL_Surface *m_screen;

  SDL_Renderer *m_renderer;

public:

  Screen();

  bool init();

  bool loadMedia(  Texture *texture, Texture *texture_2 );

  void renderSeq( Texture *texture, Texture *texture_2 );

  void close();

};

#endif
