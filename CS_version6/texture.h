// Johnathan Regha-Dodge: CS_version6/texture.h
// Texture class

#ifndef TEXTURE_H
#define TEXTURE_H

// Including IO stream and the necessary files
#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "src/include/SDL2/SDL_ttf.h"

class Texture
{

private:

  // Texture object
  SDL_Texture *m_texture;

  // Dimension variables
  int m_width;
  int m_height;

public:

  // Constructor and Destructor
  Texture();
  ~Texture();

  // Class method prototypes
  bool loadFromFile( SDL_Renderer *renderer, const char* path );
  bool loadFromRenderedText( std::string texture_text, SDL_Color text_color, TTF_Font *font, SDL_Renderer *renderer );

  void free();
  void render( SDL_Renderer *renderer, int x, int y );

  int getWidth();
  int getHeight();

};

#endif
