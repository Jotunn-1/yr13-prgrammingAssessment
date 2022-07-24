//Johnathan Regha-Dodge: CS_version6/screen.h
//Screen class

#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <limits>
#include "texture.h"
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_TTF.h"

class Player;
class Enemy;
class Enemies;
class Projectile;

class Screen
{

public:

  const int SCREEN_WIDTH = 1920;
  const int SCREEN_HEIGHT = 1080;
  const int SCREEN_FPS = 60;
  const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

private:

  SDL_Window *m_window;

  SDL_Surface *m_screen;

  SDL_Renderer *m_renderer;

public:

  Screen();

  bool init();
  bool loadMedia(  Texture *texture, Texture *texture_2, Texture *texture_3, Texture *texture_4, Texture *font_texture,TTF_Font *font);

  int fpsCalc( int counted_frames );

  void renderSeq( Player *player, Enemies *enemies, Projectile *projectile, Texture *texture, Texture *texture_2, Texture *texture_3, Texture *texture_4, Texture *font_texture );
  void close( TTF_Font *font );

};

#endif
