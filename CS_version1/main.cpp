//Johnathan Regha-Dodge: CS_version1

#include <limits>
#include "sprites.cpp"


//Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates Window
bool init();

//Loads Media
bool loadMedia();

//Close SDL window
void close();

//window to render to
SDL_Window* window = NULL;

SDL_Surface *screen = NULL;

SDL_Surface *player = NULL;

SDL_Surface *background = NULL;

Player mPlayer;

SDL_Rect backgroundPos;

bool init()
{

  bool success = true;

  std::cout << "Initializing" << std::endl;

  //SDL_Init returns -1 if an error occurs, function below to check for error
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

    //Assigning parameters to  create window
    window = SDL_CreateWindow( "CS_version1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if( window == NULL )
    {
      std::cout << "Window could not be created " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    //Get window surface
    screen = SDL_GetWindowSurface( window );

    return success;
}


bool loadMedia()
{

  bool success = true;

  std::cout << "Loading media" << std::endl;

  player = SDL_LoadBMP( "player.bmp" );
  background = SDL_LoadBMP( "background.bmp" );

  if( player == NULL || background == NULL )
  {
    std::cout << "Media could not be loaded " << static_cast< std::string >( SDL_GetError() ) << std::endl ;
    success = false;
  }

  return success;
}

void close()
{
  std::cout << "Closing" << std::endl;

  //Deallocate surface
  SDL_FreeSurface( player );
  player = NULL;
  SDL_FreeSurface( background );
  background = NULL;

  //Destroy window
  SDL_DestroyWindow( window );
  window = NULL;

  //Quits SDL
  SDL_Quit();
}

int main( int argc, char* args[] )
{

  if( !init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );

  }
  else
  {
    //Load Media
    if( !loadMedia() )
    {
      std::cout << "media failed " << static_cast< std::string >( SDL_GetError() ) << std::endl;

    }
    else
    {

      backgroundPos.x = 0;
      backgroundPos.y = 0;
      backgroundPos.w = 640;
      backgroundPos.h = 480;


      // Main loop flag
      bool quit = false;

      SDL_Event event;

      while( !quit )
      {

        SDL_BlitSurface(background, NULL, screen, &backgroundPos);
        SDL_BlitSurface(player, NULL, screen, &mPlayer.playerPos);

        SDL_UpdateWindowSurface( window );

        while( SDL_PollEvent( &event ) !=0 )
        {

          if( event.type == SDL_QUIT )
          {
            quit = true;
          }

          mPlayer.moveEvent( event );
        }

        mPlayer.move();
      }
    }
  }

  close();

  //Console closes once program ends or error occurs, code used to keep it open
  /*
  std::cout << "Enter to continue..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  */

  return 0;
}
