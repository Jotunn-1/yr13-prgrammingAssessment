//Johnathan Regha-Dodge: CS_version3/texture.h
//Texture class

#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

class Texture
{

private:

  SDL_Texture *m_texture;

  int m_width;
  int m_height;

public:

  Texture();

  ~Texture();

  bool loadFromFile( SDL_Renderer *renderer, const char* path );

  void free();

  void render( SDL_Renderer *renderer, int x, int y );

  int get_width();
  int get_height();

};

#endif
