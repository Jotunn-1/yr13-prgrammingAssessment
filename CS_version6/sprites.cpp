//Johnathan Regha-Dodge: CS_version6/sprites.cpp
//Class methods for the sprite class

// Include the necessary files
#include <math.h>
#include <random>
#include "sprites.h"

// Random number generator for enemy spawns
std::default_random_engine generator;
// within the parameters is the range of the number generator
std::uniform_int_distribution<int> distribution(100, 540);
std::uniform_int_distribution<int> distribution2(100, 380);

// Player class methods
Player::Player()
{
  // Creating a hitbox for the player upon construction
  hit_box = new Collisions[HIT_BOXES];
  m_posx = 1240;
  m_posy = 612;
}

Player::~Player()
{
  // De allocate memory for the created hitbox
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

float Player::getWidth()
{
  return m_width;
}

float Player::getHeight()
{
  return m_height;
}

void Player::getDimensions( Texture *texture )
{
  // Assigning the texture dimensions to the sprites
  m_width = texture->getWidth();
  m_height = texture->getHeight();
}

void Player::hp_check( Enemies *enemies )
{
  if ( enemies->player_hploss_confirm( hit_box ) )
  {
    if( health_loss )
    {
      health--;
      time_hit = SDL_GetTicks();
      health_loss = false;
    }

    if( SDL_GetTicks() > ( time_hit + 1000 ) )
    {
      health_loss = true;
    }
  }
}

void Player::moveEvent( SDL_Event &event )
{
  if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
  {
    /*
    If the type of key pressed is any of the following the
    corresponding will occur
    */
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

  // Velocity is multiplied by time step for frame independent movement
  m_velx =  temp_velx * *time_step;
  m_posx += m_velx;
  hit_box->shiftColliders( m_posx, m_posy );

  // Below if statement is used to confine the player to the screen
  if( m_posx < 0 )
  {
    m_posx = 0;
  }
  else if( m_posx > screen->SCREEN_WIDTH - m_width )
  {
    m_posx = screen->SCREEN_WIDTH - m_width;
  }

  // Velocity is multiplied by time step for frame independent movement
  m_vely = temp_vely * *time_step;
  m_posy += m_vely;
  hit_box->shiftColliders( m_posx, m_posy );

  // Below if statement is used to confine the player to the screen ( borders )
  if( m_posy < 0 )
  {
    m_posy = 0;
  }
  else if( m_posy > screen->SCREEN_HEIGHT - m_height )
  {
    m_posy = screen->SCREEN_HEIGHT - m_height;
  }
}

void Player::playerRenderer( SDL_Renderer *renderer, Texture *player_texture, Texture *heart_texture, Texture *heart_texture2, Texture *heart_texture3 )
{
  player_texture->render( renderer, (int)m_posx, (int)m_posy );

  if( health == 3 )
  {
    heart_texture->render( renderer, 10, 10 );
    heart_texture2->render( renderer, 60, 10 );
    heart_texture3->render( renderer, 110, 10 );
  } else if( health == 2 )
    {
      heart_texture->render( renderer, 10, 10 );
      heart_texture2->render( renderer, 60, 10 );
    } else if( health == 1 )
      {
        heart_texture->render( renderer, 10, 10 );
      } else if( health == 0 )
        {
         std::cout << "dead" << std::endl;
        }
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
/*
void Player::collisionShift()
{
  m_posx -=  m_velx;
  m_posy -=  m_vely;

  hit_box->shiftColliders( m_posx, m_posy );
}
*/

/*
void Player::collisionPush( float enemy_velx, float enemy_vely )
{
  m_posx += enemy_velx/3;
  m_posy += enemy_vely/3;

  hit_box->shiftColliders( m_posx, m_posy );
}
*/

/////////////////////////////////////////////////////////////////////////////////

Enemy::Enemy()
{
  // Creating a hitbox for the enemy upon construction
  hit_box = new Collisions[HIT_BOXES];
  /*
  temp_posx = 0;
  temp_posy = 0;
  */
}

Enemy::~Enemy()
{
  // De allocate memory for the created hitbox
  delete [] hit_box;
}

void Enemy::pos()
{
  std::cout<< m_posx << std::endl;
  std::cout<< m_posy << std::endl;
}

void Enemy::coords()
{
  m_posx = distribution(generator);

  m_posy = distribution2(generator);
}

void Enemy::getEnemyDimensions( Texture *texture )
{
  m_width = texture->getWidth();
  m_height = texture->getHeight();
}

void Enemy::pathFinder( int player_posx, int player_posy, float *time_step, Screen *screen, Enemy m_enemies[], int size, Player *player, Projectile *projectile )
{
  // Projectile hitbox to use later
  SDL_Rect hit_box_b = projectile->getHitBox();

  // Player hitbox to use layer
  SDL_Rect hit_box_a = player->getHitBox();

  /*
  Distance ( difference between 2 points ) added the width and height divided
  by 2 to get the center of the sprite ( since coords start at 0,0 of the texture )
  */
  float distance_x = ( player_posx + player->getWidth()/2 ) - ( m_posx + m_width/2 );
  float distance_y = ( player_posy + player->getHeight()/2 ) - ( m_posy + m_height/2 );

  // Claculation for the vector between the enemy and the player
  float vector = hypotf( distance_x, distance_y );

  // Disperse & calculation function
  // Only want it to run when there is more than one enemy
  if( size > 1 )
  {
    // Initilizing total pos variable which will be the center of mass of the enemies
    float total_x_pos = 0;
    float total_y_pos = 0;
    for( int i = 0; i < size; i++ )
    {
      /*
      Adding all the enemy positions divided by 2
      ( to get the center of the enemy ) to the total position
      */
      total_x_pos += ( m_enemies[i].m_posx + m_width/2 );
      total_y_pos += ( m_enemies[i].m_posy + m_height/2 );
    }

    /*
    Dividing by the number of enemies to get the
    average which is the center of mass
    */
    total_x_pos /= size;
    total_y_pos /= size;

    // The distance of the enemy to the center of mass
    float distance_com_x = ( total_x_pos ) - ( m_posx + m_width/2 );
    float distance_com_y = ( total_y_pos ) - ( m_posy + m_height/2 );

    // Claculation for the vector between the enemy and the center of mass
    float vector_com = hypotf( distance_com_x, distance_com_y );

    // Only disperses within a certain distance
    if( vector_com < VIEW_DISTANCE )
    {
      if( disperse_ready )
      {
        // Enemy wont move towards the player whilst dispersing
        move_ready = false;
        /*
        Normalizing the COM vector so it's just a direction ( either +ve or -ve )
        and then multiplying it by a -ve so its in the opposite direction
        */
        float disperse_direction_x = ( distance_com_x / vector_com ) * -1;
        float disperse_direction_y = ( distance_com_y / vector_com ) * -1;

        /*
        Multiplying the direction to speed ( dividing it for fine tuning ) multiplying
        it by time step for frame independent movement
        */
        m_velx = (( disperse_direction_x * ENEMY_VEL )/2) * *time_step;
        m_vely = (( disperse_direction_y * ENEMY_VEL )/2) * *time_step;

        // Adding speed to the position
        m_posx += m_velx;
        m_posy += m_vely;
      }
    }
    if( vector_com > VIEW_DISTANCE )
    {
      /*
      When the enemy is beyond the view distance the disperse function will no longer
      be true. Move ready is now true so the enemy can move towards the player
      */
      disperse_ready = false;
      move_ready = true;

      if( disperse_cooldown = -1 )
      {
        disperse_cooldown = SDL_GetTicks();
      }
    }
  }

  if( SDL_GetTicks() > ( disperse_cooldown + 500 ) )
  {
    disperse_ready = true;
    disperse_cooldown = -1;
  }

  // If the distance between the enemy and player is greater than 0
  if( vector > 0 )
  {
    if( move_ready )
    {
    // Normalizing distance between enemy and player to get the direction
    float direction_x = distance_x / vector;
    float direction_y = distance_y / vector;

    /*
    Multiplying the direction by the speed and then by time step for
    frame independent movement
    */
    m_velx = ( direction_x * ENEMY_VEL ) * *time_step;
    m_vely = ( direction_y * ENEMY_VEL ) * *time_step;

    // adding speed to position
    m_posx += m_velx;
    m_posy += m_vely;
    }
  }

  // Enemy borders
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

  // Check for collisions with player hitbox
  if( hit_box->checkCollisions( &hit_box_a ) )
  {
    m_posx -= m_velx;
    m_posy -= m_vely;
  }

  // Chcek for collisions with projectile hitbox
  if( hit_box->checkCollisions( &hit_box_b ) )
  {
    /*
    If I don't check if the state is shoot whenver the enemy runs into the player
    their position will change
    */
    if( projectile->shoot )
    {
      m_posx = distribution(generator);
      m_posy = distribution2(generator);

      projectile->enemies_eliminated++;
    }
  }

  // To keep the enemy hitbox on the enemy
  hit_box->shiftColliders( m_posx, m_posy );
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

SDL_Rect Enemy::getHitbox()
{
  return hit_box->getColliders();
}

////////////////////////////////////////////////////////////////////////////////

Enemies::Enemies()
{
  // Creating N_ENEMIES number of enemies upon construction
  m_enemies = new Enemy[ N_ENEMIES ];
}

Enemies::~Enemies()
{
  // De allocatie memory for all enemies
  delete [] m_enemies;
}

void Enemies::getPos()
{
  // For every enemy run the get position class method
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].pos();
  }
}

void Enemies::getCoords()
{
  // For every enemy run the get coords class method
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].coords();
  }
}

bool Enemies::player_hploss_confirm( Collisions *hit_box_player )
{
  SDL_Rect hit_box_enemy;
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    hit_box_enemy = m_enemies[i].getHitbox();

    if( hit_box_player->checkCollisions( &hit_box_enemy ) )
    {
      return true;
    }

  }
}

void Enemies::update( int player_posx, int player_posy, float *time_step, Screen *screen, Player *player, Projectile *projectile )
{
  // For every enemy run the path finding class method
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    int size = N_ENEMIES;
    m_enemies[i].pathFinder( player_posx, player_posy, time_step, screen, m_enemies, size, player, projectile);
  }
}

void Enemies::enemiesRenderer( SDL_Renderer *renderer, Texture *enemy_texture )
{
  // For every enemy run the render class method
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].enemyRenderer( renderer, enemy_texture );
  }
}

void Enemies::getEnemiesDimensions( Texture *texture )
{
  // For every enemy run the get enemy dimensions class method
  for( int i = 0; i < Enemies::N_ENEMIES; i++ )
  {
    m_enemies[i].getEnemyDimensions( texture );
  }
}

////////////////////////////////////////////////////////////////////////////////

Collisions::Collisions()
{
  // Hit box rect dimensions
  m_collider.w = 20;
  m_collider.h = 40;
}

SDL_Rect Collisions::getColliders()
{
  return m_collider;
}

void Collisions::shiftColliders( float m_posx, float m_posy )
{
  // Match the hitbox to the sprites position
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
  // Initializing sprite edges variables
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  // Declaring sprite edges variables
  left_a = m_collider.x;
  left_b = hit_box_a->x;

  right_a = m_collider.x + m_collider.w;
  right_b = hit_box_a->x + hit_box_a->w;

  top_a = m_collider.y;
  top_b = hit_box_a->y;

  bottom_a = m_collider.y + m_collider.h;
  bottom_b = hit_box_a->y + hit_box_a->h;

  // If collision
  if( bottom_a >= top_b && right_a >= left_b && left_a <= right_b && top_a <= bottom_b )
  {
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile()
{
  // Creating a hit for the projectile upon construction
  hit_box = new Collisions[HIT_BOXES];

  shoot = false;
}

Projectile::~Projectile()
{
  // De allocate memory for the created hitbox
  delete [] hit_box;
}

void Projectile::getDimensions( Texture *texture )
{
  m_width = texture->getWidth();
  m_height= texture ->getHeight();
}

void Projectile::projectileRenderer( SDL_Renderer *renderer, Texture *projectile_texture )
{
  // If the projectile is being shot render the texture
  if( shoot )
  {
    projectile_texture->render( renderer, (int)m_posx, (int)m_posy );
  }
}

void Projectile::trajectory( Player *player, float *time_step)
{
  // While the projectile isn't shot calculate the trajectory
  if( !shoot )
  {
    cursor_pos = SDL_GetMouseState( &m_cursorx, &m_cursory );

    // std::cout << m_cursorx << std::endl;
    // std::cout << m_cursory << std::endl;

    float distance_x = ( m_cursorx ) - ( m_posx + m_width/2 );
    float distance_y = ( m_cursory ) - ( m_posy + m_height/2 );

    float vector = hypotf( distance_x, distance_y );

    float direction_x = distance_x / vector;
    float direction_y = distance_y / vector;

    m_velx = ( direction_x * VEL ) * *time_step;
    m_vely = ( direction_y * VEL ) * *time_step;

    m_posx = player->getPosx();
    m_posy = player->getPosy();

    timer_start = true;
  }

  if( shoot )
  {
    if( timer_start )
    {
      bullet_start_time = SDL_GetTicks();
    }
    int bullet_time = SDL_GetTicks();

    // std::cout << "test" << std::endl;
    m_posx += m_velx;
    m_posy += m_vely;

    timer_start = false;

    // Bullet duration
    if( bullet_time > bullet_start_time + 350 )
    {
      shoot = false;
    }
  }

  // std::cout << m_posx << std::endl;
  // std::cout << m_posy << std::endl;

  hit_box->shiftColliders( m_posx, m_posy );
  // hit_box->HitBox();
}

void Projectile::moveEvent( SDL_Event &event )
{

  switch( event.type )
  {
    case SDL_MOUSEBUTTONDOWN:
      if( event.button.button == SDL_BUTTON_LEFT )
      {
        shoot = true;
      }
  }
}

SDL_Rect Projectile::getHitBox()
{
  return hit_box->getColliders();
}
