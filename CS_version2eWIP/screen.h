#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <limits>
#include "texture.h"
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

class Player;
class Enemy;
class Enemies;

class Screen
{

public:

  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
  const int SCREEN_FPS = 60;
  const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

private:

  SDL_Window *m_window;

  SDL_Surface *m_screen;

  SDL_Renderer *m_renderer;

public:

  Screen();

  bool init();
  bool loadMedia(  Texture *texture, Texture *texture_2, Texture *texture_3 );

  int fpsCalc( int counted_frames );

  void renderSeq( Player *player, Enemies *enemies, Texture *texture, Texture *texture_2, Texture *texture_3 );
  void close();

};

#endif
