#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include <cmath>
#include <vector>

#include "texture.h"
#include "screen.h"
#include "src/include/SDL2/SDL.h"

class Player;
class Enemy;
class Enemies;
class Collisions;

class Player
{
private:

  Collisions *hit_box;

  float m_velx, m_vely;
  float m_posx, m_posy;

  float temp_velx, temp_vely;

  int m_width, m_height;
  const int HIT_BOXES = 1;


public:

  static const int VEL = 480;

  Player();
  virtual ~Player();

  float getPosx();
  float getPosy();

  void getDimensions( Texture *texture );
  void moveEvent( SDL_Event &event );
  void move( float *time_step, Screen *screen );
  void playerRenderer( SDL_Renderer *renderer, Texture *player_texture);
  SDL_Rect getHitBox();
  //debug
  void printHitBox();
  void collisionShift( int test );
};

class Enemy
{
private:

  Collisions *hit_box;

  float m_posx, m_posy;
  float m_velx, m_vely;

  int m_width, m_height;
  int disperse_cooldown = -1;
  const int HIT_BOXES = 1;

  bool move_ready = true;
  bool disperse_ready = true;


public:

  static const int ENEMY_VEL = 320;

  static const int VIEW_DISTANCE = 100;

  Enemy();
  virtual ~Enemy();

  void pos();
  void coords( Screen *screen );
  void getEnemyDimensions( Texture *texture );
  void pathFinder( int player_posx, int player_posy, float *time_step, Screen *screen, Enemy m_enemies[], int size, Player *player );
  void enemyRenderer( SDL_Renderer *renderer, Texture *enemy_texture );
  //debug
  void printHitBox();

};

class Enemies
{
public:
  static const int N_ENEMIES = 1;

private:
  Enemy *m_enemies;

public:
  Enemies();
  virtual ~Enemies();

  void getPos();
  void getCoords( Screen *screen );
  void update( int player_posx, int player_posy, float *time_step, Screen *screen, Player *player );
  void enemiesRenderer( SDL_Renderer *renderer, Texture *enemy_texture );
  void getEnemiesDimensions( Texture *texture );

};

class Collisions
{
private:

  SDL_Rect m_collider;

public:

  int test;

  Collisions();

  SDL_Rect getColliders();

  void shiftColliders( float m_posx, float m_posy );
  //debug
  void HitBox();

  bool checkCollisions( SDL_Rect *a );

};

#endif
