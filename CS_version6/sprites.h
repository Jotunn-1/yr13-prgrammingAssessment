//Johnathan Regha-Dodge: CS_version6/sprites.h
//Sprite class

#ifndef SPRITES_H
#define SPRITES_H

// Including IO stream and necessary files
#include <iostream>
#include <cmath>
#include <vector>

#include "texture.h"
#include "screen.h"
#include "src/include/SDL2/SDL.h"

/*
  Forward declaration of collision
  collision is used before the creation of the class
*/

class Collisions;
class Enemies;
class Enemy;

class Player
{
private:

  // Collision object
  Collisions *hit_box;

  // Speed & position variables
  float m_velx, m_vely;
  float m_posx, m_posy;
  float temp_velx, temp_vely;

  // Dimension variables
  int m_width, m_height;

  const int HIT_BOXES = 1;


public:

  int health = 3;
  bool health_loss = true;
  int time_hit;

  // The value the sprite velocity will be added by
  static const int VEL = 480;

  // Constructor & destructor
  Player();
  virtual ~Player();

  // Class method prototypes
  float getPosx();
  float getPosy();

  float getVelx();
  float getVely();

  float getWidth();
  float getHeight();

  void getDimensions( Texture *texture );
  void hp_check( Enemies *enemies );
  void moveEvent( SDL_Event &event );
  void move( float *time_step, Screen *screen );
  void playerRenderer( SDL_Renderer *renderer, Texture *player_texture , Texture *heart_texture, Texture *heart_texture2, Texture *heart_texture3 );
  SDL_Rect getHitBox();
  //debug
  void printHitBox();
  // void collisionShift();
  // void collisionPush( float enemy_velx, float enemy_vely );
};

class Enemy
{
private:

  // Collision object
  Collisions *hit_box;

  // Speed & position variables
  float m_posx, m_posy;
  float m_velx, m_vely;
  //float temp_posx, temp_posy;

  // Dimension variables
  int m_width, m_height;
  int disperse_cooldown = -1;

  const int HIT_BOXES = 1;

  // Disperse function conditions
  bool move_ready = true;
  bool disperse_ready = true;


public:

  // The value the sprite velocity will be added by
  static const int ENEMY_VEL = 260;

  // The distance condition for the disperse function
  static const int VIEW_DISTANCE = 100;

  // Constructur & destructor
  Enemy();
  virtual ~Enemy();

  // Class method prototypes
  void pos();
  void coords();
  bool player_hploss_check();
  void getEnemyDimensions( Texture *texture );
  void pathFinder( int player_posx, int player_posy, float *time_step, Screen *screen, Enemy m_enemies[], int size, Player *player, Projectile *projectile );
  void enemyRenderer( SDL_Renderer *renderer, Texture *enemy_texture );
  //debug
  void printHitBox();

  SDL_Rect getHitbox();

};

// Class that handles the creation and control of all enemies
class Enemies
{
public:

  // Number of enemies
  static const int N_ENEMIES = 10;

private:

  // Enemy object
  Enemy *m_enemies;

public:

  // Constructor & destructor
  Enemies();
  virtual ~Enemies();

  // Class method prototypes
  void getPos();
  void getCoords();
  bool player_hploss_confirm( Collisions *hit_box_player );
  void update( int player_posx, int player_posy, float *time_step, Screen *screen, Player *player, Projectile *projectile);
  void enemiesRenderer( SDL_Renderer *renderer, Texture *enemy_texture );
  void getEnemiesDimensions( Texture *texture );

};

class Collisions
{
private:

  // Rect object
  SDL_Rect m_collider;

public:

  // Collision conditions
  bool temp_check = false;
  bool collided_top = NULL;
  bool collided_bottom= NULL;
  bool collided_left = NULL;
  bool collided_right = NULL;

  // Constructor
  Collisions();

  // Class method prototypes
  SDL_Rect getColliders();
  void shiftColliders( float m_posx, float m_posy );
  //debug
  void HitBox();
  bool checkCollisions( SDL_Rect *a );

};

class Projectile
{
private:

  // Collision object
  Collisions *hit_box;

  // Speed & position variables
  float m_velx, m_vely;
  float m_posx, m_posy;

  // Bullet time & condition
  int bullet_start_time;
  bool timer_start;

  // Cursor position
  Uint32 cursor_pos;
  int m_cursorx, m_cursory;

  // Dimension variables
  int m_width, m_height;

  const int HIT_BOXES = 1;

public:

  int enemies_eliminated;

  // Bullet condition
  bool shoot;

  // The value the sprite velocity will be added by
  static const int VEL = 960;

  // Constructor and destructor
  Projectile();
  virtual ~Projectile();

  // Class method prototypes
  void getDimensions( Texture *texture );
  void projectileRenderer( SDL_Renderer *renderer, Texture *projectile_texture );
  void trajectory( Player *player, float *time_step );
  void moveEvent( SDL_Event &event );
  SDL_Rect getHitBox();

};

#endif
