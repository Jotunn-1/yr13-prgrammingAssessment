#include "sprites.h"

void Player::getDimensions( Texture *player_texture )
{
  m_width = player_texture->get_width();
  m_height = player_texture->get_height();

}

void Player::moveEvent( SDL_Event &event )
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

void Player::move( float *time_step, Screen *screen )
{

  m_posx += m_velx * *time_step;

  if( m_posx < 0 )
  {
    m_posx = 0;
  }
  else if( m_posx > screen->SCREEN_WIDTH - m_width )
  {
    m_posx = screen->SCREEN_WIDTH - m_width;
  }

  m_posy += m_vely * *time_step;

  if( m_posy < 0 )
  {
    m_posy = 0;
  }
  else if( m_posy > screen->SCREEN_HEIGHT - m_height )
  {
    m_posy = screen->SCREEN_HEIGHT - m_height;
  }

}

void Player::tempRenderName( SDL_Renderer *renderer, Texture *player_texture )
{
  player_texture->render( renderer, (int)m_posx, (int)m_posy );
}
