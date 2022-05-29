#include <stdlib.h>
#include <time.h>
#include <random>
#include "sprites.h"

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 640);
std::uniform_int_distribution<int> distribution2(0, 480);

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



/////////////////////////////////////////////////////////////////////////////////

void Enemy::tempPathFinder( int player_posx, int player_posy, float *time_step, Screen *screen )
{
  float direction_x = player_posx - m_posx;
  float direction_y = player_posy - m_posy;

  float vector = hypotf( direction_x, direction_y );

  if( vector > 0 )
  {
    float vector_x = direction_x / vector;
    float vector_y = direction_y / vector;

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
  //std::cout << m_posx << std::endl;
  enemy_texture->render( renderer, (int)m_posx, (int)m_posy );
}

void Enemy::coords( Screen *screen )
{
  m_posx = distribution(generator);
  std::cout << m_posx << std::endl;

  m_posy = distribution2(generator);
  std::cout << m_posy << std::endl;
}

void Enemy::pos()
{
  std::cout<< m_posx << std::endl;
  std::cout<< m_posy << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

Enemies::Enemies()
{
  m_enemies = new Enemy[ N_ENEMIES ];
}

Enemies::~Enemies()
{
  delete [] m_enemies;
}

void Enemies::getPos()
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].pos();
  }
}

void Enemies::getCoords( Screen *screen )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    srand( time( NULL ) );
    m_enemies[i].coords( screen );
  }
}

void Enemies::enemiesDimensions( Texture *texture )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].getDimensions( texture );
  }
}

void Enemies::update( int player_posx, int player_posy, float *time_step, Screen *screen )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].tempPathFinder( player_posx, player_posy, time_step, screen );
  }
}

void Enemies::tempEnemiesRender( SDL_Renderer *renderer, Texture *enemy_texture )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].tempEnemyRender( renderer, enemy_texture );
  }
}
