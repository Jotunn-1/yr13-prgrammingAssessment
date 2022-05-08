//Class: screen.h
#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include "src/include/SDL2/SDL.h"

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

  //Screen constructor
  Screen();

  //Screen class method prototypes
  bool init();
  int fpsCalc( int countedFrames );
  void close( SDL_Surface *surface_1, SDL_Surface *surface_2 );
  void blit( SDL_Surface *surface_1, SDL_Surface *surface_2, SDL_Rect rect_1, SDL_Rect rect_2 );
};

#endif
