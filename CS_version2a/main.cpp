#include <iostream>
#include <limits>

#include "texture.cpp"
#include "screen.cpp"
#include "sprites.cpp"

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

Screen screen;

Player player;

Texture player_texture;
Texture background;

int counted_frames = 0;

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

  player.getDimensions( &player_texture );

  bool quit = false;

  SDL_Event event;

  while( !quit )
  {

    int beginning_of_tick = SDL_GetTicks();
    int step_timer_start;

    int fps = screen.fpsCalc( counted_frames );
    std::cout << fps << std::endl;

    while( SDL_PollEvent( &event ) != 0 )
    {

      if( event.type == SDL_QUIT )
      {
        quit = true;
      }

      player.moveEvent( event );
    }

    float time_step = ( SDL_GetTicks() - step_timer_start ) / 1000.f;

    player.move( &time_step, &screen );

    step_timer_start = SDL_GetTicks();

    screen.renderSeq( &player, &player_texture, &background );

    ++counted_frames;

    int frame_ticks = ( SDL_GetTicks() - beginning_of_tick );
    if( frame_ticks < screen.SCREEN_TICKS_PER_FRAME )
    {
      SDL_Delay( screen.SCREEN_TICKS_PER_FRAME - frame_ticks );
    }

  }

  screen.close();

  return 0;
}
