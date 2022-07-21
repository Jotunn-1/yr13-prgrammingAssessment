#include <math.h>
#include <random>
#include "sprites.h"

//account for size of characters later
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(100, 540);
std::uniform_int_distribution<int> distribution2(100, 380);

Player::Player()
{
  hit_box = new Collisions[HIT_BOXES];
}

Player::~Player()
{
  delete [] hit_box;
}

float Player::getPosx()
{
  return m_posx;
}

float Player::getPosy()
{
  return m_posy;
}

float Player::getVelx()
{
  return m_velx;
}

float Player::getVely()
{
  return m_vely;
}

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
      case SDLK_w: temp_vely -= VEL; break;
      case SDLK_s: temp_vely += VEL; break;
      case SDLK_a: temp_velx -= VEL; break;
      case SDLK_d: temp_velx += VEL; break;
    }
  }
  else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
  {
    switch( event.key.keysym.sym )
    {
      case SDLK_w: temp_vely += VEL; break;
      case SDLK_s: temp_vely -= VEL; break;
      case SDLK_a: temp_velx += VEL; break;
      case SDLK_d: temp_velx -= VEL; break;
    }
  }
}

void Player::move( float *time_step, Screen *screen)
{

  m_velx =  temp_velx * *time_step;;
  m_posx += m_velx;
  hit_box->shiftColliders( m_posx, m_posy );

  if( m_posx < 0 )
  {
    m_posx = 0;
  }
  else if( m_posx > screen->SCREEN_WIDTH - m_width )
  {
    m_posx = screen->SCREEN_WIDTH - m_width;
  }

  m_vely = temp_vely * *time_step;
  m_posy += m_vely;
  hit_box->shiftColliders( m_posx, m_posy );

  if( m_posy < 0 )
  {
    m_posy = 0;
  }
  else if( m_posy > screen->SCREEN_HEIGHT - m_height )
  {
    m_posy = screen->SCREEN_HEIGHT - m_height;
  }
}

void Player::playerRenderer( SDL_Renderer *renderer, Texture *player_texture )
{
  player_texture->render( renderer, (int)m_posx, (int)m_posy );
}

SDL_Rect Player::getHitBox()
{
  return hit_box->getColliders();
}

void Player::printHitBox()
{
  std::cout << "player" << std::endl;
  hit_box->HitBox();
  std::cout << "x - " << m_posx << std::endl;
  std::cout << "y - " << m_posy << std::endl;
  std::cout << " " << std::endl;
}

void Player::collisionShift()
{
  m_posx -=  m_velx;
  m_posy -=  m_vely;

  hit_box->shiftColliders( m_posx, m_posy );
}

void Player::collisionPush( float enemy_velx, float enemy_vely )
{
  m_posx += enemy_velx/3;
  m_posy += enemy_vely/3;

  hit_box->shiftColliders( m_posx, m_posy );
}

/////////////////////////////////////////////////////////////////////////////////

Enemy::Enemy()
{
  hit_box = new Collisions[HIT_BOXES];
  temp_posx = 0;
  temp_posy = 0;
}

Enemy::~Enemy()
{
  delete [] hit_box;
}

void Enemy::pos()
{
  std::cout<< m_posx << std::endl;
  std::cout<< m_posy << std::endl;
}

void Enemy::coords( Screen *screen )
{
  m_posx = distribution(generator);

  m_posy = distribution2(generator);
}

void Enemy::getEnemyDimensions( Texture *texture )
{
  m_width = texture->get_width();
  m_height = texture->get_height();
}

void Enemy::pathFinder( int player_posx, int player_posy, float *time_step, Screen *screen, Enemy m_enemies[], int size, Player *player )
{

  SDL_Rect hit_box_a = player->getHitBox();

  // center, which is why I add
  float direction_x = ( player_posx + 10 ) - ( m_posx + 10 );
  float direction_y = ( player_posy + 20 ) - ( m_posy + 20 );

  float vector = hypotf( direction_x, direction_y );

  // avoid clumping
  if( size > 1 )
  {
    float total_x_pos = 0;
    float total_y_pos = 0;
    for( int i = 0; i < size; i++ )
    {
        total_x_pos += m_enemies[i].m_posx;
        total_y_pos += m_enemies[i].m_posy;
    }

    total_x_pos /= size;
    total_y_pos /= size;

    float distance_com_x = ( total_x_pos + 10 ) - ( m_posx + 10 );
    float distance_com_y = ( total_y_pos + 20 ) - ( m_posy + 20 );

    float vector_com = hypotf( distance_com_x, distance_com_y );

    if( vector_com < VIEW_DISTANCE )
    {
      if( disperse_ready )
      {
        move_ready = false;
        float disperse_vector_x = ( distance_com_x / vector_com ) * -1;
        float disperse_vector_y = ( distance_com_y / vector_com ) * -1;

        m_velx = (( disperse_vector_x * ENEMY_VEL )/2) * *time_step;
        m_vely = (( disperse_vector_y * ENEMY_VEL )/2) * *time_step;

        m_posx += m_velx;
        m_posy += m_vely;
      }
    }

    if( vector_com > VIEW_DISTANCE )
    {
      disperse_ready = false;
      move_ready = true;

      if( disperse_cooldown = -1 )
      {
        disperse_cooldown = SDL_GetTicks();
      }
    }
  }

  if( vector > 0 )
  {
    if( move_ready )
    {
    float vector_x = direction_x / vector;
    float vector_y = direction_y / vector;

    m_velx = ( vector_x * ENEMY_VEL ) * *time_step;
    m_vely = ( vector_y * ENEMY_VEL ) * *time_step;

    m_posx += m_velx;
    hit_box->shiftColliders( m_posx, m_posy );
    m_posy += m_vely;
    hit_box->shiftColliders( m_posx, m_posy );
    }
  }

  if( SDL_GetTicks() > ( disperse_cooldown + 500 ) )
  {
    disperse_ready = true;
    disperse_cooldown = -1;
  }

  if( m_posx < 0 )
  {
    m_posx = 0;
  }
  else if( m_posx > screen->SCREEN_WIDTH - m_width )
  {
    m_posx = screen->SCREEN_WIDTH - m_width;
  }

  if( m_posy < 0 )
  {
    m_posy = 0;
  }
  else if( m_posy > screen->SCREEN_HEIGHT - m_height )
  {
    m_posy = screen->SCREEN_HEIGHT - m_height;
  }

  if( !hit_box->temp_check )
  {
    temp_posx = m_posx;
    temp_posy = m_posy;
  }

  if( hit_box->checkCollisions( &hit_box_a ) )
  {

    if( hit_box->collided_top )
    {
      m_posy -= m_vely/3;
    }
    if( hit_box->collided_bottom )
    {
      m_posy -= m_vely/3;
    }
    if( hit_box->collided_right)
    {
      m_posx -= m_velx/3;
    }
    if( hit_box->collided_left )
    {
      m_posx -= m_velx/3;
    }

    hit_box->temp_check = true;

    // player->collisionShift();

    // m_posx = temp_posx;
    // m_posy = temp_posy;

    player->collisionPush( m_velx, m_vely );

    m_posx += player->getVelx();
    m_posy += player->getVely();

    hit_box->shiftColliders( m_posx, m_posy );
  }

  if( !hit_box->checkCollisions( &hit_box_a ) )
  {
    // hit_box->temp_check = false;
    hit_box->collided_top = false;
    hit_box->collided_left = false;
    hit_box->collided_right = false;
    hit_box->collided_bottom = false;
  }
}

void Enemy::enemyRenderer( SDL_Renderer *renderer, Texture *enemy_texture )
{
  //std::cout << m_posx << std::endl;
  enemy_texture->render( renderer, (int)m_posx, (int)m_posy );
}

void Enemy::printHitBox()
{
  std::cout << "enemy" << std::endl;
  hit_box->HitBox();
  std::cout << "x - " << m_posx << std::endl;
  std::cout << "y - " << m_posy << std::endl;
  std::cout << " " << std::endl;
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

void Enemies::update( int player_posx, int player_posy, float *time_step, Screen *screen, Player *player )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    int size = N_ENEMIES;
    m_enemies[i].pathFinder( player_posx, player_posy, time_step, screen, m_enemies, size, player );
  }
}

void Enemies::enemiesRenderer( SDL_Renderer *renderer, Texture *enemy_texture )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].enemyRenderer( renderer, enemy_texture );
  }
}

void Enemies::getEnemiesDimensions( Texture *texture )
{
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].getEnemyDimensions( texture );
  }
}

////////////////////////////////////////////////////////////////////////////////

// Collisions::Collisions()
// {
//   m_collider.resize(1);
//
//   m_collider[0].w = 20;
//   m_collider[0].h = 40;
// }
//
// std::vector<const SDL_Rect*> &Collisions::getColliders()
// {
//   return m_collider;
// }
//
// void Collisions::shiftColliders( float m_posx, float m_posy )
// {
//   m_collider[0].x = m_posx;
//   m_collider[0].y = m_posy;
// }

Collisions::Collisions()
{
  m_collider.w = 20;
  m_collider.h = 40;
}

SDL_Rect Collisions::getColliders()
{
  return m_collider;
}

void Collisions::shiftColliders( float m_posx, float m_posy )
{
  m_collider.x = m_posx;
  m_collider.y = m_posy;
}

void Collisions::HitBox()
{
  std::cout << "x - " << m_collider.x << std::endl;
  std::cout << "y - " << m_collider.y << std::endl;
}

bool Collisions::checkCollisions( SDL_Rect *hit_box_a )
{
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  left_a = m_collider.x;
  left_b = hit_box_a->x;

  right_a = m_collider.x + m_collider.w;
  right_b = hit_box_a->x + hit_box_a->w;

  top_a = m_collider.y;
  top_b = hit_box_a->y;

  bottom_a = m_collider.y + m_collider.h;
  bottom_b = hit_box_a->y + hit_box_a->h;

  if( bottom_a >= top_b && right_a >= left_b && left_a <= right_b && top_a <= bottom_b )
  {
    std::cout << "collision detected" << std::endl;
    if( bottom_a >= top_b )
    {
      std::cout << "1" << std::endl;
      collided_top = true;
    }
    if( right_a >= left_b )
    {
      std::cout << "2" << std::endl;
      collided_left = true;
    }
    if( left_a <= right_b )
    {
      std::cout << "3" << std::endl;
      collided_right = true;
    }
    if( top_a <= bottom_b )
    {
      std::cout << "4" << std::endl;
      collided_bottom = true;
    }
    std::cout << "done" << std::endl;
    return true;
  }

  return false;
}
