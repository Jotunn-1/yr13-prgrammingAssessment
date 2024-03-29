//Johnathan Regha-Dodge: CS_version1/main.cpp
//Main file of the project

//imports
#include <limits>
#include "sprites.cpp"
#include "screen.cpp"
#include "load_media.cpp"

//Screen object
Screen screen;

//Player object
Player player;

//Media object
LoadMedia media;

//Background pos rect (temp)
SDL_Rect background_pos;

int countedFrames = 0;

// main function
int main( int argc, char* args[] )
{

  //Checking to see if screen initialized
  if( !screen.init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );

  }
  else
  {
    //Checking to see if media initialized
    if( !media.loadMedia() )
    {
      std::cout << "media failed " << static_cast< std::string >( SDL_GetError() ) << std::endl;

    }
    else
    {

      //Background pos rect, setting variables (temp)
      background_pos.x = 0;
      background_pos.y = 0;
      background_pos.w = 640;
      background_pos.h = 480;

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
          //If the caught event is SDL_QUIT then quit is true
          if( event.type == SDL_QUIT )
          {
            quit = true;
          }

          //Player move event class method
          player.moveEvent( event );
        }

        //Player movement class method
        player.move();

        //Screen blit class method
        screen.blit( media.m_background, media.m_player, background_pos, player.rect );
        ++countedFrames;

        // Capping frames to SCREEN_TICKS_PER_FRAME
        int frameTicks = ( start - SDL_GetTicks() );
        if( frameTicks < screen.SCREEN_TICKS_PER_FRAME )
        {
          SDL_Delay( screen.SCREEN_TICKS_PER_FRAME );
        }
      }
    }
  }

  //Screen close class method
  screen.close( media.m_background, media.m_player );

  //Console closes once program ends or error occurs, code used to keep it open
  /*
  std::cout << "Enter to continue..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  */

  return 0;
}
