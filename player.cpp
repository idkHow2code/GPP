// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0
#define _USE_MATH_DEFINES
#include "player.h"
#include <math.h>

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
    spriteData.width = playerNS::WIDTH;           // size of player
    spriteData.height = playerNS::HEIGHT;
    spriteData.x = playerNS::X;                   // location on screen
    spriteData.y = playerNS::Y;
    spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = playerNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
    startFrame = playerNS::PLAYER_START_FRAME;     // first frame of ship animation
    endFrame     = playerNS::PLAYER_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = playerNS::WIDTH/2.0;
    mass = playerNS::MASS;
    collisionType = entityNS::CIRCLE;
	hp = 20;
	pistolBuffer = 30.0f;
	shotgunBuffer = 60.0f;
	smgBuffer = 6.0f;
	rifleBuffer = 12.0f;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	audio = gamePtr->getAudio();
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.x += frameTime * velocity.x;         // move player along X 
	//spriteData.y += frameTime * velocity.y;         // move player along Y

	if (input->isKeyDown(PLAYER_RIGHT_KEY) || input->isKeyDown(PLAYER_LEFT_KEY) || input->isKeyDown(PLAYER_UP_KEY) || input->isKeyDown(PLAYER_DOWN_KEY))
	{
		if (input->isKeyDown(PLAYER_RIGHT_KEY))            // if move right
		{
			spriteData.x = spriteData.x + frameTime * PLAYER_SPEED;
			if (spriteData.x > GAME_WIDTH)               // if off screen right
				spriteData.x = ((float)-spriteData.width);  // position off screen left
		}
		if (input->isKeyDown(PLAYER_LEFT_KEY))             // if move left
		{
			spriteData.x = spriteData.x - frameTime * PLAYER_SPEED;
			if (spriteData.x < -spriteData.width)         // if off screen left
				spriteData.x = ((float)GAME_WIDTH);      // position off screen right
		}
		if (input->isKeyDown(PLAYER_UP_KEY))               // if move up
		{
			spriteData.y = spriteData.y - frameTime * PLAYER_SPEED;
			if (spriteData.y < -spriteData.height)        // if off screen top
				spriteData.y = (float)GAME_HEIGHT;     // position off screen bottom
		}

		if (input->isKeyDown(PLAYER_DOWN_KEY))             // if move down
		{
			spriteData.y = spriteData.y + frameTime * PLAYER_SPEED;
			if (spriteData.y > GAME_HEIGHT)              // if off screen bottom
				spriteData.y = ((float)-spriteData.height);    // position off screen top
		}
		startFrame = playerNS::PLAYER_START_FRAME;
		endFrame = playerNS::PLAYER_END_FRAME;
	}
	else
	{
		startFrame = playerNS::PLAYER_START_FRAME;
		endFrame = playerNS::PLAYER_START_FRAME;
		//player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
	}

	spriteData.angle = atan2(spriteData.y - input->getMouseY(), spriteData.x - input->getMouseX()) - 90;
	
	if (this->pistolBuffer != 30.0f)
	{
		pistolBuffer += 1.0f;
	}


	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - playerNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - playerNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - playerNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - playerNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}



}

void Player::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}

void Player::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}

void Player::damageMe(int damageValue)
{
	audio->playCue("scream");
	this->hp = this->hp - damageValue;
}

int Player::getHp()
{
	return this->hp;
}

void Player::setPistolBuffer(float buffer)
{
	this->pistolBuffer = buffer;
}

void Player::setShotgunBuffer(float buffer)
{
	this->shotgunBuffer = buffer;
}
void Player::setSmgBuffer(float buffer)
{
	this->smgBuffer = buffer;
}
void Player::setRifleBuffer(float buffer)
{
	this->rifleBuffer = buffer;
}



