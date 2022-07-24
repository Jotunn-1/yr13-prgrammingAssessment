//Johnathan Regha-Dodge: CS_version6/main.cpp
//Main file of the project

#include <iostream>
#include <limits>

#include "texture.cpp"
#include "screen.cpp"
#include "sprites.cpp"

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

Screen screen;

Player player;

Enemies enemies;

Projectile projectile;

Texture player_texture;
Texture enemy_texture;
Texture projectile_texture;
Texture background;
Texture font_texture;

TTF_Font *font = NULL;

int counted_frames = 0;

int main( int argc, char* args[] )
{

  if( !screen.init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
  }

  if( !screen.loadMedia( &player_texture, &background, &enemy_texture, &projectile_texture, &font_texture, font ) )
  {
    std::cout << "media failed " << static_cast< std::string >( SDL_GetError() );

  }

  player.getDimensions( &player_texture );
  enemies.getEnemiesDimensions( &enemy_texture );
  projectile.getDimensions( &projectile_texture );


  enemies.getCoords( &screen );

  bool quit = false;

  int step_timer_start = SDL_GetTicks();

  SDL_Event event;

  while( !quit )
  {
    int beginning_of_tick = SDL_GetTicks();

    // int fps = screen.fpsCalc( counted_frames );
    // std::cout << fps << std::endl;

    while( SDL_PollEvent( &event ) != 0 )
    {

      if( event.type == SDL_QUIT )
      {
        quit = true;
      }

      player.moveEvent( event );
      projectile.moveEvent( event );
    }

    float time_step = ( SDL_GetTicks() - step_timer_start ) / 1000.f;

    projectile.trajectory( &player, &time_step );

    player.move( &time_step, &screen );

    enemies.update( player.getPosx(), player.getPosy(), &time_step, &screen, &player, &projectile );

    step_timer_start = SDL_GetTicks();

    screen.renderSeq( &player, &enemies, &projectile, &player_texture, &background, &enemy_texture, &projectile_texture, &font_texture );

    ++counted_frames;

    int frame_ticks = ( SDL_GetTicks() - beginning_of_tick );
    if( frame_ticks < screen.SCREEN_TICKS_PER_FRAME )
    {
      SDL_Delay( screen.SCREEN_TICKS_PER_FRAME - frame_ticks );
    }
  }

  screen.close( font );

  return 0;
}
