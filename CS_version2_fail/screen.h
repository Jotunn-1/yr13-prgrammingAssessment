//Class: screen.h
#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include "sprites.cpp"
#include "texture.cpp"
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

class Screen
{

public:

  //Screen dimensions
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
  const int SCREEN_FPS = 60;
  const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

private:

  //Window declaration
  SDL_Window *m_window;
  //Screen declaration
  SDL_Surface *m_screen;


  int fps;

public:

  //Renderer declaration
  SDL_Renderer *m_renderer;
  
  //Screen constructor
  Screen();

  //Screen class method prototypes
  bool init();
  void renderProcess( Player *player, Texture *player_texture, Texture *background );
  int fpsCalc( int countedFrames );
  void close( Texture *texture_1, Texture *texture_2 );
  bool loadMedia( Texture *player_texture, Texture *background );
};

#endif
