#include "playerHealth.h"


//=============================================================================
// default constructor
//=============================================================================
PlayerHealth::PlayerHealth() : Entity()
{
	spriteData.width = playerHealthNS::WIDTH;
	spriteData.height = playerHealthNS::HEIGHT;
	//spriteData.x = playerHealthNS::X;                   // location on screen
	//spriteData.y = playerHealthNS::Y;
	spriteData.rect.bottom = playerHealthNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerHealthNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = playerHealthNS::PLAYERHEALTH_START_FRAME;     // first frame of ship animation
	endFrame = playerHealthNS::PLAYERHEALTH_START_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = playerHealthNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}



bool PlayerHealth::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void PlayerHealth::draw()
{
	Image::draw();              // draw ship
}

void PlayerHealth::update(float frameTime)
{
	Entity::update(frameTime);
}