//Johnathan Regha-Dodge: CS_version6/screen.cpp
//Class methods for the screen class

#include "screen.h"
#include "sprites.h"

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
    success = false;
  }

  if( TTF_Init() == -1 )
  {
    std::cout << "SDL_ttf could not initialize " << static_cast< std::string >( TTF_GetError() );
    success = false;
  }

  m_screen = SDL_GetWindowSurface( m_window );

  if( m_screen == NULL )
  {
    std::cout << "Screen could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}

bool Screen::loadMedia( Texture *texture, Texture *texture_2, Texture *texture_3, Texture *texture_4, Texture *font_texture, TTF_Font *font)
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
  if( !texture_3->loadFromFile( m_renderer, "assets/enemy.png" ) )
  {
    std::cout << "background image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !texture_4->loadFromFile( m_renderer, "assets/projectile.png" ) )
  {
    std::cout << "background image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  font = TTF_OpenFont( "assets/Fipps-Regular.otf", 28);
  if( font == NULL )
  {
    std::cout<< "Failed to load font" << static_cast< std::string>( SDL_GetError() );
    success = false;
  }
  else
  {
    SDL_Color text_color = { 0, 0, 0 };
    if( !font_texture->loadFromRenderedText("Testing", text_color, font, m_renderer ) )
    {
      std::cout<< "Failed to render text texture" << std::endl;
      success = false;
    }
  }
  return success;
}

int Screen::fpsCalc( int counted_frames )
{
  float fps = counted_frames / ( SDL_GetTicks() / 1000.f );
  if( fps > 2000000 )
  {
    fps = 0;
  }

  return fps;
}

void Screen::renderSeq( Player *player, Enemies *enemies, Projectile *projectile, Texture *texture, Texture *texture_2, Texture *texture_3, Texture *texture_4, Texture *font_texture )
{
  SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear( m_renderer );

  texture_2->render( m_renderer, 0, 0 );

  player->playerRenderer( m_renderer, texture);

  enemies->enemiesRenderer( m_renderer, texture_3 );

  projectile->projectileRenderer( m_renderer, texture_4 );

  font_texture->render( m_renderer, ( SCREEN_WIDTH - font_texture->getWidth() ) / 2, ( SCREEN_HEIGHT - font_texture->getHeight() ) / 2 );

  SDL_RenderPresent( m_renderer );
}

void Screen::close( TTF_Font *font )
{
  std::cout << "Closing" << std::endl;

  SDL_FreeSurface( m_screen );
  m_screen = NULL;

  TTF_CloseFont( font );
  font = NULL;

  SDL_DestroyWindow( m_window );
  SDL_DestroyRenderer( m_renderer );
  m_window = NULL;
  m_renderer = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
