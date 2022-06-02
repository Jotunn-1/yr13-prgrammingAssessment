#include <math.h>
#include <random>
#include "sprites.h"

//account for size of characters later
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(100, 540);
std::uniform_int_distribution<int> distribution2(100, 380);

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

void Enemy::tempPathFinder( int player_posx, int player_posy, float *time_step, Screen *screen, Enemy m_enemies[], int size )
{
  float direction_x = player_posx - m_posx;
  float direction_y = player_posy - m_posy;

  float vector = hypotf( direction_x, direction_y );

  // avoid clumping
  float total_x_pos = 0;
  float total_y_pos = 0;
  for( int i = 0; i < size; i++ )
  {
      total_x_pos += m_enemies[i].m_posx;
      total_y_pos += m_enemies[i].m_posy;
  }

  total_x_pos /= size;
  total_y_pos /= size;

  float distance_com_x = total_x_pos - m_posx;
  float distance_com_y = total_y_pos - m_posy;

  float vector_com = hypotf( distance_com_x, distance_com_y );

  if( vector > 0 )
  {
    if( move )
    {
    float vector_x = direction_x / vector;
    float vector_y = direction_y / vector;

    m_posx += ( vector_x * ENEMY_VEL ) * *time_step;
    m_posy += ( vector_y * ENEMY_VEL ) * *time_step;
    }
  }

  // if( vector_com < VIEW_DISTANCE )
  // {
  //   if( last_move == -1 )
  //   {
  //     last_move = SDL_GetTicks();
  //     std::cout <<"----"<< last_move << std::endl;
  //   }
  //
  //   if( vector_com < )
  //   {
  //     move = false;
  //     float test_vector_x = ( distance_com_x / vector_com ) * -1;
  //     float test_vector_y = ( distance_com_y / vector_com ) * -1;
  //
  //     m_posx += ( test_vector_x * ENEMY_VEL ) * *time_step;
  //     m_posy += ( test_vector_y * ENEMY_VEL ) * *time_step;
  //   }
  //   else if( SDL_GetTicks() > ( last_move + 2000) )
  //   {
  //     move = true;
  //     last_move = -1;
  //   }
  // }

  // std::cout << "1 " << test << std::endl;

  if( vector_com < VIEW_DISTANCE )
  {
    if( test )
    {
      // std::cout << test << std::endl;
      move = false;
      float test_vector_x = ( distance_com_x / vector_com ) * -1;
      float test_vector_y = ( distance_com_y / vector_com ) * -1;

      m_posx += ( test_vector_x * ENEMY_VEL ) * *time_step;
      m_posy += ( test_vector_y * ENEMY_VEL ) * *time_step;
    }
  }

  // std::cout << "2 " << test << std::endl;

  // std::cout << "COM " << vector_com << std::endl;
  // std::cout << "VIEW DISTANCE " << VIEW_DISTANCE << std::endl;

  if( vector_com > VIEW_DISTANCE )
  {
    test = false;
    move = true;

    if( temp_time = -1 )
    {
      temp_time = SDL_GetTicks();
    }
  }

  if( SDL_GetTicks() > ( temp_time + 500 ) )
  {
    test = true;
    temp_time = -1;
  }

  // if( m_posx < 0 )
  // {
  //   m_posx = 0;
  // }
  // else if( m_posx > screen->SCREEN_WIDTH - m_width )
  // {
  //   m_posx = screen->SCREEN_WIDTH - m_width;
  // }
  //
  // m_posy += m_vely * *time_step;
  //
  // if( m_posy < 0 )
  // {
  //   m_posy = 0;
  // }
  // else if( m_posy > screen->SCREEN_HEIGHT - m_height )
  // {
  //   m_posy = screen->SCREEN_HEIGHT - m_height;
  // }
}

void Enemy::tempEnemyRender( SDL_Renderer *renderer, Texture *enemy_texture )
{
  //std::cout << m_posx << std::endl;
  enemy_texture->render( renderer, (int)m_posx, (int)m_posy );
}

void Enemy::coords( Screen *screen )
{
  m_posx = distribution(generator);

  m_posy = distribution2(generator);
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
    int size = N_ENEMIES;
    m_enemies[i].tempPathFinder( player_posx, player_posy, time_step, screen, m_enemies, size);
  }
}

void Enemies::tempEnemiesRender( SDL_Renderer *renderer, Texture *enemy_texture )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].tempEnemyRender( renderer, enemy_texture );
  }
}
