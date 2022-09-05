// Johnathan Regha-Dodge: CS_version6/screen.h
// Screen class

#ifndef SCREEN_H
#define SCREEN_H

// Including IO stream and the necessary files
#include <iostream>
#include <limits>
#include "texture.h"
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_TTF.h"

// Forward declaration
// If included in this file then I will have circular dependencies ( same file included multiple times)
class Player;
class Enemy;
class Enemies;
class Projectile;

class Screen
{

public:

  // Constant class variables
  const int SCREEN_WIDTH = 1240;
  const int SCREEN_HEIGHT = 612;
  const int SCREEN_FPS = 60;
  const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

private:

  // SDL screen related objects
  SDL_Window *m_window;

  SDL_Surface *m_screen;

  SDL_Renderer *m_renderer;

public:

  // Constructor
  Screen();

  // Class method prototypes
  bool init();
  bool loadMedia(  Texture *texture, Texture *texture_2, Texture *texture_3, Texture *texture_4, Texture *font_texture,
                   TTF_Font *font , Texture *heart_texture, Texture *heart_texture2, Texture *heart_texture3);

  int fpsCalc( int counted_frames );

  void renderSeq( Player *player, Enemies *enemies, Projectile *projectile, Texture *texture, Texture *texture_2, Texture *texture_3,
                  Texture *texture_4, Texture *font_texture , Texture *heart_texture, Texture *heart_texture2, Texture *heart_texture3 );
  void close( TTF_Font *font );

};

#endif
