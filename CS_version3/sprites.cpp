//Johnathan Regha-Dodge: CS_version3/sprites.cpp
//Class methods for the sprite class

#include "sprites.h"

void Player::getDimensions( Texture *texture )
{
  m_width = texture->get_width();
  m_height = texture->get_height();

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

int Player::getPosx()
{
  return m_posx;
}

int Player::getPosy()
{
  return m_posy;
}

void Enemy::tempPathFinder( int player_posx, int player_posy, float *time_step, Screen *screen )
{
  float direction_x = player_posx - m_posx;
  float direction_y = player_posy - m_posy;

  float vector = hypotf( direction_x, direction_y );
  if( vector > 0 )
  {
    float vector_x = direction_x / vector;
    float vector_y = direction_y / vector;

    std::cout << ( vector_x * ENEMY_VEL ) * *time_step << std::endl;

    m_posx += ( vector_x * ENEMY_VEL ) * *time_step;
    m_posy += ( vector_y * ENEMY_VEL ) * *time_step;
  }

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

void Enemy::tempEnemyRender( SDL_Renderer *renderer, Texture *enemy_texture )
{
  enemy_texture->render( renderer, (int)m_posx, (int)m_posy );
}
