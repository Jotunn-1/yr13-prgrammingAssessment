//Johnathan Regha-Dodge: CS_version1/screen.cpp
//Class methods for the screen class

//Imports
#include "screen.h"

//Sets below class variables to NULL upon creation of object
Screen::Screen(): m_window(NULL), m_screen(NULL) {}

//Class method init
bool Screen::init()
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
    m_window = SDL_CreateWindow( "CS_version1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //Checking if window has been initialized
    if( m_window == NULL )
    {
      std::cout << "Window could not be created " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    //Get window surface
    m_screen = SDL_GetWindowSurface( m_window );

    //Checking if screen has been initialized
    if( m_screen == NULL )
    {
      std::cout << "Screen could not be created " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    return success;
}

//Class method to calculate fps
int Screen::fpsCalc( int countedFrames )
{
  float fps = countedFrames / ( SDL_GetTicks() / 1000.f );
  if( fps > 2000000 )
  {
    fps = 0;
  }

  return fps;
}

//Class method to deallocate memory from surfaces
void Screen::close( SDL_Surface *surface_1, SDL_Surface *surface_2 )
{
  std::cout << "Closing" << std::endl;

  //Deallocate surface
  SDL_FreeSurface( surface_1 );
  surface_1 = NULL;
  SDL_FreeSurface( surface_2 );
  surface_2 = NULL;

  //Destroy window
  SDL_DestroyWindow( m_window );
  m_window = NULL;

  //Quits SDL
  SDL_Quit();
}

//Class method to blit surfaces to the screen
void Screen::blit( SDL_Surface *surface_1, SDL_Surface *surface_2, SDL_Rect rect_1, SDL_Rect rect_2 )
{
  //First parameter: surface to blit; third parameter: surface to blit to; fourth parameter: rectangle that the surface is copied to (allows me to modify x and y)
  SDL_BlitSurface( surface_1, NULL, m_screen, &rect_1 );
  SDL_BlitSurface( surface_2, NULL, m_screen, &rect_2 );

  SDL_UpdateWindowSurface( m_window );
}
