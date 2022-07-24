//Johnathan Regha-Dodge: CS_version1/sprites.cpp
//Class methods for the sprite class

//Imports
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
  //Catches key down events
  if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
  {
    //if the keydown event was of any of these types it will do the corresponding.
    switch( event.key.keysym.sym )
    {
      case SDLK_w: mVelY -= VEL; break;
      case SDLK_s: mVelY += VEL; break;
      case SDLK_a: mVelX -= VEL; break;
      case SDLK_d: mVelX += VEL; break;
    }
  }
  //key up event reverses that of the up event
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

  //player movement on the x axis
  rect.x += mVelX;

  //If statement stops player from moving off screen
  if( ( rect.x + mWidth ) > 640 )
  {
    rect.x -= mVelX;
  }

  //player movement on the y axis
  rect.y += mVelY;

  //If statement stops player from moving off screen
  if( ( rect.y + mHeight ) > 480 )
  {
    rect.y -= mVelY;
  }

}
