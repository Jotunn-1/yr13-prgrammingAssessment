//Johnathan Regha-Dodge: CS_version6/screen.cpp
//Class methods for the screen class

// Including the screen & sprite class
#include "screen.h"
#include "sprites.h"

// Screen constructor, initializing the SDL class variables
Screen::Screen():
  m_window(NULL), m_screen(NULL), m_renderer(NULL){}

// Class method to initialize the screen
bool Screen::init()
{
  bool success = true;

  std::cout << "Initializing" << std::endl;

  // Initialized & checking if SDL has been initialized
  if( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  // Creating the window
  m_window = SDL_CreateWindow( "CS_version6", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

  // Checking if the window has been initialized
  if( m_window == NULL )
  {
    std::cout << "Window could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  // Creating the renderer
  m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );

  // Checking if the renderer has been initialized
  if( m_renderer == NULL )
  {
    std::cout << "Renderer could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  int img_flags = IMG_INIT_PNG;

  // Initializing & checking if SDL_IMG has been initialized
  if( !( IMG_Init( img_flags ) & img_flags ) )
  {
    std::cout << "SDL_image could not initialize " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  // Initializing & checking if SDL_TTF (text) has been initialized
  if( TTF_Init() == -1 )
  {
    std::cout << "SDL_ttf could not initialize " << static_cast< std::string >( TTF_GetError() );
    success = false;
  }

  // Creating a screen from the window surface
  m_screen = SDL_GetWindowSurface( m_window );

  // Checking if the screen has been initialized
  if( m_screen == NULL )
  {
    std::cout << "Screen could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}

// Class method for loading the images
bool Screen::loadMedia( Texture *texture, Texture *texture_2, Texture *texture_3, Texture *texture_4, Texture *font_texture,
                        TTF_Font *font , Texture *heart_texture, Texture *heart_texture2, Texture *heart_texture3)
{

  bool success = true;

  std::cout << "Loading media" << std::endl;

  //Initializing & checking if following images have been initialized
  if( !texture->loadFromFile( m_renderer, "assets2/player.png" ) )
  {
    std::cout << "player image failed to laod " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !texture_2->loadFromFile( m_renderer, "assets2/background.png" ) )
  {
    std::cout << "background image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !texture_3->loadFromFile( m_renderer, "assets2/enemy.png" ) )
  {
    std::cout << "enemy image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !texture_4->loadFromFile( m_renderer, "assets2/projectile.png" ) )
  {
    std::cout << "projectile image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !heart_texture->loadFromFile( m_renderer, "assets2/heart.png" ) )
  {
    std::cout << "heart image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !heart_texture2->loadFromFile( m_renderer, "assets2/heart.png" ) )
  {
    std::cout << "heart image 2 failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !heart_texture3->loadFromFile( m_renderer, "assets2/heart.png" ) )
  {
    std::cout << "heart image 3 failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  // Assigning font variable
  font = TTF_OpenFont( "assets2/Fipps-Regular.otf", 28);
  // Checking if font variable has been initialzed
  if( font == NULL )
  {
    std::cout<< "Failed to load font" << static_cast< std::string>( SDL_GetError() );
    success = false;
  }
  else
  {
    SDL_Color text_color = { 0, 0, 0 };
    // Initializing & checking if text has been initialzed
    if( !font_texture->loadFromRenderedText("CLEAN UP 100 TRASH", text_color, font, m_renderer ) )
    {
      std::cout<< "Failed to render text texture" << std::endl;
      success = false;
    }
  }
  return success;
}

// Class method for Calculating fps
int Screen::fpsCalc( int counted_frames )
{
  // Deviding the number of frames by the number of ticks in seconds
  float fps = counted_frames / ( SDL_GetTicks() / 1000.f );
  if( fps > 2000000 )
  {
    fps = 0;
  }

  return fps;
}

// Class method for the render sequence
void Screen::renderSeq( Player *player, Enemies *enemies, Projectile *projectile, Texture *texture, Texture *texture_2,
                        Texture *texture_3, Texture *texture_4, Texture *font_texture , Texture *heart_texture, Texture *heart_texture2, Texture *heart_texture3 )
{
  // Mot sure if renderer color is necessary as of now
  SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  // Clearing what previously had been rendered
  SDL_RenderClear( m_renderer );

  // Render sequence
  texture_2->render( m_renderer, 0, 0 );

  player->playerRenderer( m_renderer, texture, heart_texture, heart_texture2, heart_texture3 );

  enemies->enemiesRenderer( m_renderer, texture_3 );

  projectile->projectileRenderer( m_renderer, texture_4 );

  font_texture->render( m_renderer, ( SCREEN_WIDTH - font_texture->getWidth() - 10 ), 0 );

  SDL_RenderPresent( m_renderer );
}

// Class method to close the program
void Screen::close( TTF_Font *font )
{
  std::cout << "Closing" << std::endl;

  // Freeing resources
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
