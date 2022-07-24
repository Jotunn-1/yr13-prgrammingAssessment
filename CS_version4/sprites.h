//Johnathan Regha-Dodge: CS_version4/sprites.h
//Sprite class

#ifndef SPRITES_H
#define SPRITES_H

#include <iostream>
#include <cmath>

#include "texture.h"
#include "screen.h"
#include "src/include/SDL2/SDL.h"

class Player
{
private:

  float m_velx, m_vely;
  float m_posx, m_posy;

  int m_width, m_height;

public:

  static const int VEL = 480;

  int getPosx();
  int getPosy();

  void getDimensions( Texture *texture );
  void moveEvent( SDL_Event &event );
  void move( float *time_step, Screen *screen );
  void tempRenderName( SDL_Renderer *renderer, Texture *player_texture);
};

class Enemy: public Player
{
private:

  float m_posx, m_posy;
  float m_velx, m_vely;

  int m_width, m_height;

  int temp_time = -1;

  bool move = true;

  bool test = true;

public:

  static const int ENEMY_VEL = 320;

  static const int VIEW_DISTANCE = 50;

  void tempPathFinder( int player_posx, int player_posy, float *time_step, Screen *screen, Enemy m_enemies[], int size);
  void tempEnemyRender( SDL_Renderer *renderer, Texture *enemy_texture );
  void coords( Screen *screen );
  void pos();

};

class Enemies
{
public:
  static const int N_ENEMIES = 8;

private:
  Enemy *m_enemies;

public:
  Enemies();
  virtual ~Enemies();

  void getPos();
  void getCoords( Screen *screen );
  void enemiesDimensions( Texture *texture );
  void update( int player_posx, int player_posy, float *time_step, Screen *screen );
  void tempEnemiesRender( SDL_Renderer *renderer, Texture *enemy_texture );

};

#endif