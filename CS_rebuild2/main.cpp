#include <iostream>
#include <limits>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "texture.cpp"

SDL_Window *g_window = NULL;

SDL_Surface *g_screen = NULL;

SDL_Renderer *g_renderer = NULL;

bool init();

bool loadMedia();

void close();

/*
class Texture
{

private:

  SDL_Texture *m_texture;

  int m_width;
  int m_height;

public:

  Texture();

  ~Texture();

  bool loadFromFile( const char* path );

  void free();

  void render( int x, int y );

  int get_width();
  int get_height();

};

Texture::Texture(): m_texture( NULL ) {}
Texture::~Texture()
{
  free();
}

void Texture::free()
{
  if( m_texture != NULL )
  {
    SDL_DestroyTexture( m_texture );
    m_texture = NULL;
  }
}

void Texture::render( int x, int y)
{
  SDL_Rect render_quad = { x, y, m_width, m_height };
  SDL_RenderCopy( g_renderer, m_texture, NULL, &render_quad );
}

int Texture::get_width()
{
  return m_width;
}

int Texture::get_height()
{
  return m_height;
}

bool Texture::loadFromFile( const char *path )
{

  free();

  SDL_Texture *new_texture = NULL;

  SDL_Surface *loaded_surface = IMG_Load( path );
  if( loaded_surface == NULL )
  {
    std::cout << "Loaded surface not created " << static_cast< std::string >( SDL_GetError() );
  }

  new_texture = SDL_CreateTextureFromSurface( g_renderer, loaded_surface );
  if( new_texture == NULL )
  {
    std::cout << "New texture could not be created " << static_cast< std::string >( SDL_GetError() );
  }

  m_width = loaded_surface->w;
  m_height = loaded_surface->h;

  SDL_FreeSurface( loaded_surface );

  m_texture = new_texture;
  return m_texture !=NULL;

}
*/

Texture player;
Texture background;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init()
{
  bool success = true;

  std::cout << "Initializing" << std::endl;

  if( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  g_window = SDL_CreateWindow( "CS_render_test1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

  if( g_window == NULL )
  {
    std::cout << "Window could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  g_renderer = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED );
  if( g_renderer == NULL )
  {
    std::cout << "Renderer could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  int img_flags = IMG_INIT_PNG;

  if( !( IMG_Init( img_flags ) & img_flags ) )
  {
    std::cout << "SDL_image could not initialize " << static_cast< std::string >( SDL_GetError() );
  }

  g_screen = SDL_GetWindowSurface( g_window );

  if( g_screen == NULL )
  {
    std::cout << "Screen could not be created " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}

bool loadMedia()
{

  bool success = true;

  std::cout << "Loading media" << std::endl;

  if( !player.loadFromFile( g_renderer, "assets/player.png" ) )
  {
    std::cout << "player image failed to laod " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }
  if( !background.loadFromFile( g_renderer, "assets/background.png" ) )
  {
    std::cout << "background image failed to load " << static_cast< std::string >( SDL_GetError() );
    success = false;
  }

  return success;
}

void close()
{
  std::cout << "Closing" << std::endl;

  SDL_FreeSurface( g_screen );
  g_screen = NULL;

  SDL_DestroyWindow( g_window );
  g_window = NULL;

  SDL_Quit();
}

int main( int argc, char* args[] )
{

  if( !init() )
  {
    std::cout << "Initialization failed " << static_cast< std::string >( SDL_GetError() );
  }

  if( !loadMedia() )
  {
    std::cout << "media failed " << static_cast< std::string >( SDL_GetError() );

  }

  bool quit = false;

  SDL_Event event;

  while( !quit )
  {
    while( SDL_PollEvent( &event ) != 0 )
    {

      if( event.type == SDL_QUIT )
      {
        quit = true;
      }
    }

    SDL_RenderClear( g_renderer );

    background.render( g_renderer, 0, 0 );

    player.render( g_renderer, 100, 100 );

    SDL_RenderPresent( g_renderer );

  }

  close();

  return 0;
}
