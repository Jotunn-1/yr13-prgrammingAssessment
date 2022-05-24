//Class methods: screen.cpp
#include "screen.h"

//Sets below class variables to NULL upon creation of object
Screen::Screen(): m_window(NULL), m_screen(NULL), m_renderer(NULL) {}

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

    if( m_window == NULL )
    {
      std::cout << "Window could not be created " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );

    if ( m_renderer == NULL )
    {
      std::cout << "Renderer could not be created " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    //Initialize PNG loading
    int img_flags = IMG_INIT_PNG;
    if( !( IMG_Init( img_flags ) & img_flags ) )
    {
      std::cout << "SDL_image could not initialize! " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    //Get window surface
    m_screen = SDL_GetWindowSurface( m_window );

    if( m_screen == NULL )
    {
      std::cout << "Screen could not be created " << static_cast< std::string >( SDL_GetError() );
      success = false;
    }

    return success;
}

int Screen::fpsCalc( int countedFrames )
{
  float fps = countedFrames / ( SDL_GetTicks() / 1000.f );
  if( fps > 2000000 )
  {
    fps = 0;
  }

  return fps;
}

//Class method close
void Screen::close( Texture *texture_1, Texture *texture_2 )
{
  std::cout << "Closing" << std::endl;

  //Deallocate surface
  texture_1->free();
  texture_2->free();

  //Destroy window
  SDL_DestroyRenderer( m_renderer );
  SDL_DestroyWindow( m_window );
  m_window = NULL;
  m_renderer = NULL;

  //Quits SDL
  IMG_Quit();
  SDL_Quit();
}

bool Screen::loadMedia( Texture *player_texture, Texture *background )
{

  bool success = true;

  std::cout << "Loading media" << std::endl;

  //Setting .bmp files to class variables
  if( !player_texture->loadFromFile( m_renderer, "assets/player.png" ) )
  {
    std::cout << "player image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !background->loadFromFile( m_renderer, "assets/background.png") )
  {
    std::cout << "background image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}
