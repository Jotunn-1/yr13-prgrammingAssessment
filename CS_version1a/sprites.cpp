#include "sprites.h"

Player::PlayerConstruct()
{

  playerPos.w = mWidth;
  playerPos.h = mHeight;

  playerPos.x = 0;
  playerPos.y = 0;

}

void Player::moveEvent( SDL_Event& event )
{

  if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
  {

    switch( event.key.keysym.sym )
    {
      case SDLK_w: mVelY -= VEL; break;
      case SDLK_s: mVelY += VEL; break;
      case SDLK_a: mVelX -= VEL; break;
      case SDLK_d: mVelX += VEL; break;
    }
  }
  else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
  {
    switch( event.key.keysym.sym )
    {
      case SDLK_w: mVelY += VEL; break;
      case SDLK_s: mVelY -= VEL; break;
      case SDLK_a: mVelX += VEL; break;
      case SDLK_d: mVelX -= VEL; break;
    }
  }
}

void Player::move()
{

  playerPos.x += mVelX;

  playerPos.y += mVelY;

}
