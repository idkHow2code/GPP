#include "win.h"

//=============================================================================
// default constructor
//=============================================================================
Win::Win() : Entity()
{
	spriteData.width = WinNS::WIDTH;
	spriteData.height = WinNS::HEIGHT;
	spriteData.x = WinNS::X;                   // location on screen
	spriteData.y = WinNS::Y;
	spriteData.rect.bottom = WinNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WinNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = WinNS::WIN_ANIMATION_DELAY;
	startFrame = WinNS::WIN_START_FRAME;     // first frame of ship animation
	endFrame = WinNS::WIN_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = WinNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	this->initialised = false;
}

bool Win::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_Win_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_Win_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Win::draw()
{
	Image::draw();              // draw zombie
}

void Win::update(float frameTime)
{
	Entity::update(frameTime);
}