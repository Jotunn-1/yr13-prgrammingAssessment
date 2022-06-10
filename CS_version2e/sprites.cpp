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
  hit_box[0].shiftColliders( m_posx, m_posy );

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
  hit_box[0].shiftColliders( m_posx, m_posy );

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

std::vector<SDL_Rect> Player::getHitBox()
{
  return hit_box[0].getColliders();
}

void Player::printHitBox()
{
  std::cout << "player" << std::endl;
  hit_box[0].HitBox();
  std::cout << "x - " << m_posx << std::endl;
  std::cout << "y - " << m_posy << std::endl;
  std::cout << " " << std::endl;
}

void Player::collisionShift()
{
  m_posx -= m_velx/2;
  m_posy -= m_vely/2;
}

/////////////////////////////////////////////////////////////////////////////////

Enemy::Enemy()
{
  hit_box = new Collisions[HIT_BOXES];
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

  std::vector<SDL_Rect> hit_box_a = player->getHitBox();

  float direction_x = player_posx - m_posx;
  float direction_y = player_posy - m_posy;

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

    float distance_com_x = total_x_pos - m_posx;
    float distance_com_y = total_y_pos - m_posy;

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
    hit_box[0].shiftColliders( m_posx, m_posy );
    m_posy += m_vely;
    hit_box[0].shiftColliders( m_posx, m_posy );
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

  if( hit_box[0].checkCollisions( hit_box_a ) )
  {
    m_posx -= m_velx;
    m_posy -= m_vely;
    // player->collisionShift();

    // player->collisionShift();
    hit_box[0].shiftColliders( m_posx, m_posy );
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
  hit_box[0].HitBox();
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

Collisions::Collisions()
{
  m_collider.resize(1);

  m_collider[0].w = 20;
  m_collider[0].h = 40;
}

std::vector<SDL_Rect> &Collisions::getColliders()
{
  return m_collider;
}

void Collisions::shiftColliders( float m_posx, float m_posy )
{
  m_collider[0].x = m_posx;
  m_collider[0].y = m_posy;
}

void Collisions::HitBox()
{
  std::cout << "x - " << m_collider[0].x << std::endl;
  std::cout << "y - " << m_collider[0].y << std::endl;
}

bool Collisions::checkCollisions( std::vector<SDL_Rect> &hit_box_a )
{
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  left_a = m_collider[0].x;
  left_b = hit_box_a[0].x;

  right_a = m_collider[0].x + m_collider[0].w;
  right_b = hit_box_a[0].x + hit_box_a[0].w;

  top_a = m_collider[0].y;
  top_b = hit_box_a[0].y;

  bottom_a = m_collider[0].y + m_collider[0].h;
  bottom_b = hit_box_a[0].y + hit_box_a[0].h;

  // std::cout << left_a << std::endl;
  // std::cout << left_b << std::endl;
  // std::cout << right_a << std::endl;
  // std::cout << right_b << std::endl;
  // std::cout << top_a << std::endl;
  // std::cout << top_b << std::endl;
  // std::cout << bottom_a << std::endl;
  // std::cout << bottom_b << std::endl;
  // std::cout << "" << std::endl;

  if( ( ( bottom_a <= top_b ) || ( top_a >= bottom_b ) || ( right_a <= left_b ) || ( left_a >= right_b ) ) == false )
  {
    // std::cout<< "collide" <<std::endl;
    return true;
  }

  return false;
}
