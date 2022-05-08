//Class methods: sprites.cpp
#include "sprites.h"

Player::PlayerConstruct()
{

  rect.w = mWidth;
  rect.h = mHeight;

  rect.x = 0;
  rect.y = 0;

}

//Class method moveEvent
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

//Class method move
void Player::move()
{

  rect.x += mVelX;

  //If statement stops player from moving off screen
  if( ( rect.x + mWidth ) > 640 )
  {
    rect.x -= mVelX;
  }

  rect.y += mVelY;

  //If statement stops player from moving off screen
  if( ( rect.y + mHeight ) > 480 )
  {
    rect.y -= mVelY;
  }

}
