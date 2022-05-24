//Class methods: sprites.cpp
#include "sprites.h"

//Class method moveEvent
void Player::moveEvent( SDL_Event& event )
{

  if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
  {

    switch( event.key.keysym.sym )
    {
      case SDLK_w: m_vely -= VEL; break;
      case SDLK_s: m_vely += VEL; break;
      case SDLK_a: m_velx -= VEL; break;
      case SDLK_d: m_velx += VEL; break;
    }
  }
  else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
  {
    switch( event.key.keysym.sym )
    {
      case SDLK_w: m_vely += VEL; break;
      case SDLK_s: m_vely -= VEL; break;
      case SDLK_a: m_velx += VEL; break;
      case SDLK_d: m_velx -= VEL; break;
    }
  }
}

//Class method move
void Player::move()
{

  m_posx += m_velx;


  //If statement stops player from moving off screen
  if( ( m_posx + m_width ) > 640 )
  {
    m_posx -= m_velx;
  }

  m_posy += m_vely;

  //If statement stops player from moving off screen
  if( ( m_posy + m_height ) > 480 )
  {
    m_posy -= m_vely;
  }


}

void Player::renderTest( SDL_Renderer *renderer, Texture *player_texture )
{
  player_texture->render( renderer, m_posx, m_posy );
}
