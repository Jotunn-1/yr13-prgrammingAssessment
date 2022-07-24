//Johnathan Regha-Dodge: CS_version1/load_media.cpp
//Class methods for loading media class

//imports
#include "load_media.h"

//Class method loadMedia
bool LoadMedia::loadMedia()
{

  bool success = true;

  std::cout << "Loading media" << std::endl;

  //Setting .bmp files to class variables
  m_player = SDL_LoadBMP( "assets/player.bmp" );
  m_background = SDL_LoadBMP( "assets/background.bmp" );

  //Error check
  if( m_player == NULL || m_background == NULL )
  {
    std::cout << "Media could not be loaded " << static_cast< std::string >( SDL_GetError() ) << std::endl ;
    success = false;
  }

  return success;
}
