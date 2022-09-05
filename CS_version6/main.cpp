// Johnathan Regha-Dodge: CS_version6/main.cpp
// Main file of the project


// Allows for input and outputs in code
#include <iostream>
#include <limits>

// Including all my class/class methods
#include "texture.cpp"
#include "screen.cpp"
#include "sprites.cpp"

// Including the SDL & SDL image library
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

// Screen object
Screen screen;

// Player object
Player player;

// Enemy object
Enemies enemies;

// Projectile object
Projectile projectile;

// Texture objects
Texture player_texture;
Texture enemy_texture;
Texture projectile_texture;
Texture background;
Texture font_texture;
Texture heart_texture;
Texture heart_texture2;
Texture heart_texture3;

// Creating a font
TTF_Font *font = NULL;

// Counted frames variable
int counted_frames = 0;

bool win;
bool lose;

// Main function
int main( int argc, char* args[] )
{
  // Checking if screen has been initialized, will close the program otherwise
  if( !screen.init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
  }

  // Checking if media has been initialized, will close the program otherwise
  if( !screen.loadMedia( &player_texture, &background, &enemy_texture, &projectile_texture, &font_texture, font, &heart_texture, &heart_texture2, &heart_texture3) )
  {
    std::cout << "media failed " << static_cast< std::string >( SDL_GetError() );

  }

  // Getting the dimensions and giving it to the textures
  player.getDimensions( &player_texture );
  enemies.getEnemiesDimensions( &enemy_texture );
  projectile.getDimensions( &projectile_texture );

  // Getting enemy coords
  enemies.getCoords();

  // While loop variable
  bool quit = false;

  // Start of the step
  int step_timer_start = SDL_GetTicks();

  // Object for the SDL events
  SDL_Event event;

  // Game loop
  while( !quit )
  {
    int beginning_of_tick = SDL_GetTicks();

    // int fps = screen.fpsCalc( counted_frames );
    // std::cout << fps << std::endl;

    // Poll events ( checking for events )
    while( SDL_PollEvent( &event ) != 0 )
    {
      if( event.type == SDL_QUIT )
      {
        quit = true;
      }

      player.moveEvent( event );
      projectile.moveEvent( event );
    }

    // Calculate time step for frame independent movement
    float time_step = ( SDL_GetTicks() - step_timer_start ) / 1000.f;

    // Calculate projectile trajectory
    projectile.trajectory( &player, &time_step );

    // Check which key has been pressed
    player.move( &time_step, &screen );

    // Updates each enemy
    enemies.update( player.getPosx(), player.getPosy(), &time_step, &screen, &player, &projectile );
    player.hp_check( &enemies );

    // Reset the step timer after the sprites have been moved
    step_timer_start = SDL_GetTicks();

    // Rendering all the sprites
    screen.renderSeq( &player, &enemies, &projectile, &player_texture, &background, &enemy_texture,
                      &projectile_texture, &font_texture, &heart_texture, &heart_texture2, &heart_texture3 );

    // For frame calculation
    // ++counted_frames;

    if( projectile.enemies_eliminated == 100 )
    {
      win = true;
      quit = true;
    }

    if( player.health == 0 )
    {
      lose = true;
      quit = true;
    }

    // Capping framerate
    int frame_ticks = ( SDL_GetTicks() - beginning_of_tick );
    if( frame_ticks < screen.SCREEN_TICKS_PER_FRAME )
    {
      SDL_Delay( screen.SCREEN_TICKS_PER_FRAME - frame_ticks );
    }
  }

  screen.close( font );

  //Console closes once program ends or error occurs, code used to keep it open
  if( win )
  {
    std::cout<< "YOU HAVE WON" << std::endl;
  }

  if( lose )
  {
    std::cout<< "YOU HAVE LOST" << std::endl;
  }
  
  std::cout << "Enter to continue..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


  return 0;
}
