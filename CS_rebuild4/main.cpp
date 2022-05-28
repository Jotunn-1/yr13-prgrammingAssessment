#include <iostream>
#include <limits>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "texture.cpp"
#include "screen.cpp"
#include "sprites.cpp"

Screen screen;

Player player;

Texture player_texture;
Texture background;

int main( int argc, char* args[] )
{

  if( !screen.init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
  }

  if( !screen.loadMedia( &player_texture, &background ) )
  {
    std::cout << "media failed " << static_cast< std::string >( SDL_GetError() );

  }

  bool quit = false;

  SDL_Event event;

  while( !quit )
  {
    while( SDL_PollEvent( &event ) != 0 )
    {

      if( event.type == SDL_QUIT )
      {
        quit = true;
      }

      player.moveEvent( event );
    }

    player.move();

    screen.renderSeq( &player, &player_texture, &background );

  }

  screen.close();

  return 0;
}
