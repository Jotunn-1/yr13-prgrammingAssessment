//Class: texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL.h"

class Texture
{

private:

  SDL_Texture *m_texture;

  int m_width;
  int m_height;

public:

  //Constructor
  Texture();

  //Destructor
  ~Texture();

  //Loads image from given path
  bool loadFromFile( SDL_Renderer *renderer, const char* path );

  //Free texture class method
  void free();

  //Render class method
  void render( SDL_Renderer *renderer, int x, int y );

  //Image dimensions
  int getWidth();
  int getHeight();

};

#endif
