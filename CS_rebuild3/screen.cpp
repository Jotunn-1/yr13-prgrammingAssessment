#include "screen.h"

Screen::Screen():
  m_window(NULL), m_screen(NULL), m_renderer(NULL){}

bool Screen::init()
{
  bool success = true;

  std::cout << "Initializing" << std::endl;

  if( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  m_window = SDL_CreateWindow( "CS_render_test1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

  if( m_window == NULL )
  {
    std::cout << "Window could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
  if( m_renderer == NULL )
  {
    std::cout << "Renderer could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  int img_flags = IMG_INIT_PNG;

  if( !( IMG_Init( img_flags ) & img_flags ) )
  {
    std::cout << "SDL_image could not initialize " << static_cast< std::string >( SDL_GetError() );
  }

  m_screen = SDL_GetWindowSurface( m_window );

  if( m_screen == NULL )
  {
    std::cout << "Screen could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}

bool Screen::loadMedia( Texture *texture, Texture *texture_2 )
{

  bool success = true;

  std::cout << "Loading media" << std::endl;

  if( !texture->loadFromFile( m_renderer, "assets/player.png" ) )
  {
    std::cout << "player image failed to laod " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !texture_2->loadFromFile( m_renderer, "assets/background.png" ) )
  {
    std::cout << "background image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}

void Screen::renderSeq( Texture *texture, Texture *texture_2 )
{
  SDL_RenderClear( m_renderer );

  texture_2->render( m_renderer, 0, 0 );

  texture->render( m_renderer, 100, 100 );

  SDL_RenderPresent( m_renderer );
}

void Screen::close()
{
  std::cout << "Closing" << std::endl;

  SDL_FreeSurface( m_screen );
  m_screen = NULL;

  SDL_DestroyWindow( m_window );
  m_window = NULL;

  SDL_Quit();
}
