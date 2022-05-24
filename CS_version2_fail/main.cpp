//Johnathan Regha-Dodge: main.cpp

#include <limits>
#include "sprites.cpp"
#include "screen.cpp"
#include "texture.cpp"

//Screen object
Screen screen;

//Player object
Player player;

//Texture object
Texture player_texture;
Texture background;

int countedFrames = 0;

// main function
int main( int argc, char* args[] )
{

  //Checking to see if screen initialized
  if( !screen.init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );

  }

  //Checking to see if media initialized
  if( !screen.loadMedia( &player_texture, &background ) )
  {
    std::cout << "media failed " << static_cast< std::string >( SDL_GetError() ) << std::endl;

  }

  //Main loop flag
  bool quit = false;

  //Event information
  SDL_Event event;

  //Main loop
  while( !quit )
  {

    int start = SDL_GetTicks();

    int fps = screen.fpsCalc( countedFrames );
    std::cout << fps << std::endl;

    //Checking for events
    while( SDL_PollEvent( &event ) !=0 )
    {

      if( event.type == SDL_QUIT )
      {
        quit = true;
      }

      //Player move event class method
      player.moveEvent( event );
    }

    //Player movement class method
    player.move();

    SDL_RenderClear( screen.m_renderer );

    background.render( screen.m_renderer, 0, 0);

    player.renderTest( screen.m_renderer, player_texture );

    SDL_RenderPresent( screen.m_renderer );

    ++countedFrames;

    int frameTicks = ( start - SDL_GetTicks() );
    if( frameTicks < screen.SCREEN_TICKS_PER_FRAME )
    {
      SDL_Delay( screen.SCREEN_TICKS_PER_FRAME - frameTicks );
    }
  }

  //Screen close class method
  screen.close( &player_texture, &background );

  //Console closes once program ends or error occurs, code used to keep it open
  /*
  std::cout << "Enter to continue..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  */

  return 0;
}
