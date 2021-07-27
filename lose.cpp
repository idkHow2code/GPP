#include "lose.h"

//=============================================================================
// default constructor
//=============================================================================
Lose::Lose() : Entity()
{
	spriteData.width = LoseNS::WIDTH;
	spriteData.height = LoseNS::HEIGHT;
	spriteData.x = LoseNS::X;                   // location on screen
	spriteData.y = LoseNS::Y;
	spriteData.rect.bottom = LoseNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = LoseNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = LoseNS::LOSE_ANIMATION_DELAY;
	startFrame = LoseNS::LOSE_START_FRAME;     // first frame of ship animation
	endFrame = LoseNS::LOSE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = LoseNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	loop = false;
	this->initialised = false;
}

bool Lose::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_Lose_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_Lose_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Lose::draw()
{
	Image::draw();              // draw zombie
}

void Lose::update(float frameTime)
{
	Entity::update(frameTime);
}