#include "instruction.h"

//=============================================================================
// default constructor
//=============================================================================
Instruction::Instruction() : Entity()
{
	spriteData.width = instructionNS::WIDTH;
	spriteData.height = instructionNS::HEIGHT;
	spriteData.x = instructionNS::X;                   // location on screen
	spriteData.y = instructionNS::Y;
	spriteData.rect.bottom = instructionNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = instructionNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = instructionNS::INSTRUCTION_ANIMATION_DELAY;
	startFrame = instructionNS::INSTRUCTION_START_FRAME;     // first frame of ship animation
	endFrame = instructionNS::INSTRUCTION_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = instructionNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	this->initialised = true;
}

bool Instruction::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Instruction::draw()
{
	Image::draw();              // draw zombie
}

void Instruction::update(float frameTime)
{
	Entity::update(frameTime);
}