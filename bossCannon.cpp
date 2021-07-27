#include "bossCannon.h"

//=============================================================================
// default constructor
//=============================================================================
BossCannon::BossCannon() : Entity()
{
	spriteData.width = Cannon::WIDTH;
	spriteData.height = Cannon::HEIGHT;
	spriteData.x = Cannon::X;              // location on screen
	spriteData.y = Cannon::Y;
	velocity.x = 0;
	velocity.y = 0;
	radius = Cannon::COLLISION_RADIUS;
	startFrame = Cannon::CANNON_START_FRAME;    // first frame of ship animation
	endFrame = Cannon::CANNON_END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;
}

void BossCannon::draw()
{
	if (getActive())
	{
		Image::draw();
	}
	
}
bool BossCannon::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	CannonBall.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	CannonBall.setFrames(Cannon::CANNON_START_FRAME, Cannon::CANNON_END_FRAME);
	CannonBall.setCurrentFrame(Cannon::CANNON_START_FRAME);
	CannonBall.setLoop(true);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void BossCannon::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}

int BossCannon::getdamage()
{
	return damage;
}
void BossCannon::setVelocityX(float newX)
{
	velocity.x = newX;
}

void BossCannon::setVelocityY(float newY)
{
	velocity.y = newY;
}


