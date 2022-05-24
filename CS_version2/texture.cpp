//Class methods: texture.cpp
#include "texture.h"

Texture::Texture():  m_texture(NULL) {}
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

void Texture::render( SDL_Renderer *renderer, int x, int y)
{
  SDL_Rect render_quad = { x, y, m_width, m_height };
  SDL_RenderCopy( renderer, m_texture, NULL, &render_quad );
}

int Texture::getWidth()
{
  return m_width;
}

int Texture::getHeight()
{
  return m_height;
}

bool Texture::loadFromFile( SDL_Renderer *renderer, const char* path )
{

  free();

  SDL_Texture *new_texture = NULL;

  SDL_Surface *loaded_surface = IMG_Load( path );
  if( loaded_surface == NULL )
  {
    std::cout << "Loaded surface not created " << static_cast< std::string >( SDL_GetError() );
  }

  new_texture = SDL_CreateTextureFromSurface( renderer, loaded_surface );
  if( new_texture == NULL )
  {
    std::cout << "New texture could not be created " << static_cast< std::string >( SDL_GetError() );
  }

  m_width = loaded_surface -> w;
  m_height = loaded_surface -> h;

  SDL_FreeSurface( loaded_surface );

  m_texture = new_texture;
  return m_texture !=NULL;
}
