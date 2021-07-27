#include "start.h"

//=============================================================================
// default constructor
//=============================================================================
Start::Start() : Entity()
{
	spriteData.width = startNS::WIDTH;
	spriteData.height = startNS::HEIGHT;
	spriteData.x = startNS::X;                   // location on screen
	spriteData.y = startNS::Y;
	spriteData.rect.bottom = startNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = startNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = startNS::START_ANIMATION_DELAY;
	startFrame = startNS::START_START_FRAME;     // first frame of ship animation
	endFrame = startNS::START_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = startNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	this->initialised = true;
}

bool Start::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Start::draw()
{
	Image::draw();              // draw zombie
}

void Start::update(float frameTime)
{
	Entity::update(frameTime);
}