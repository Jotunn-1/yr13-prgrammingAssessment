// Johnathan Regha-Dodge: CS_version6/texture.cpp
// Class methods for texture class

// Include the texture class
#include "texture.h"

// Constructor and Destructor methods
Texture::Texture(): m_texture( NULL ) {}
Texture::~Texture()
{
  free();
}

// Class method to free memory from the texture
void Texture::free()
{
  if( m_texture != NULL )
  {
    SDL_DestroyTexture( m_texture );
    m_texture = NULL;
  }
}


// Class method to render
void Texture::render( SDL_Renderer *renderer, int x, int y)
{
  SDL_Rect render_quad = { x, y, m_width, m_height };
  SDL_RenderCopy( renderer, m_texture, NULL, &render_quad );
}

// Class method to get the width
int Texture::getWidth()
{
  return m_width;
}

// Class method to get the height
int Texture::getHeight()
{
  return m_height;
}

// Class method to create textures
bool Texture::loadFromFile( SDL_Renderer *renderer, const char *path )
{

  free();

  SDL_Texture *new_texture = NULL;

  SDL_Surface *loaded_surface = IMG_Load( path );
  // Check if the loaded surface has been initialized
  if( loaded_surface == NULL )
  {
    std::cout << "Loaded surface not created " << static_cast< std::string >( SDL_GetError() );
  }

  new_texture = SDL_CreateTextureFromSurface( renderer, loaded_surface );
  // Check if the created texture has been initialized
  if( new_texture == NULL )
  {
    std::cout << "New texture could not be created " << static_cast< std::string >( SDL_GetError() );
  }

  // Assign the dimension class variables to the dimensions of the loaded surface
  m_width = loaded_surface->w;
  m_height = loaded_surface->h;

  // loaded surface is now unused ( used to create new_texture ) therefore we can free the allocated memory
  SDL_FreeSurface( loaded_surface );

  // Assign texture class variable to the new texture
  m_texture = new_texture;

  return m_texture !=NULL;

}

// Class method to create rendered texts
bool Texture::loadFromRenderedText( std::string texture_text, SDL_Color text_color, TTF_Font *font, SDL_Renderer *renderer)
{
  free();

  // Creating a text
  SDL_Surface* text = TTF_RenderText_Solid( font, texture_text.c_str() ,text_color );
  // Check if the text has been initialized
  if( text == NULL )
  {
    std::cout << "Unable to render text surface! SDL_ttf Error: " << static_cast< std::string >( SDL_GetError() );
  }
  else
  {
    // Creating texture from the text
    m_texture = SDL_CreateTextureFromSurface( renderer, text );
    // Check if the texture created from the text has been initialized
    if( m_texture == NULL )
    {
      std::cout << "Unable to create texture from rendered text! SDL Error: " << static_cast< std::string >( SDL_GetError() );
    }
    else
    {
      // Assign the dimension class variables to the dimensions of the loaded surface
      m_width = text->w;
      m_height = text->h;
    }

    // text is now unused ( used to create m_texture ) therefore we can free the allocated memory
    SDL_FreeSurface( text );
  }

  return m_texture != NULL;
}
