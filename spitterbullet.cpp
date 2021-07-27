#include "spitterbullet.h"

//=============================================================================
// default constructor
//=============================================================================
Spitterbullet::Spitterbullet() : Entity()
{
	spriteData.width = spitterbulletNS::WIDTH;
	spriteData.height = spitterbulletNS::HEIGHT;
	spriteData.x = spitterbulletNS::X;                   // location on screen
	spriteData.y = spitterbulletNS::Y;
	spriteData.rect.bottom = spitterbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = spitterbulletNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = spitterbulletNS::SPITTERBULLET_ANIMATION_DELAY;
	startFrame = spitterbulletNS::SPITTERBULLET_START_FRAME;     // first frame of ship animation
	endFrame = spitterbulletNS::SPITTERBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = spitterbulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	wallVector.x = 0;
	wallVector.y = 0;
}

bool Spitterbullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Spitterbullet::draw()
{
	Image::draw();              // draw zombie
}

void Spitterbullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
}
void Spitterbullet::ai(float frameTime, Spitterbullet &ent)
{
	//spriteData.x = spriteData.x + frameTime * zombieNS::ZOMBIE_SPEED;
}
int Spitterbullet::getDamage()
{
	return spitterbulletNS::DAMAGE;

}


int Spitterbullet::getWallVectorX()
{
	return this->wallVector.x;
}
int Spitterbullet::getWallVectorY()
{
	return this->wallVector.y;
}
void Spitterbullet::setWallVector(VECTOR2 vector)
{
	this->wallVector = vector;
}


void Spitterbullet::setEndFrame(int end)
{
	this->endFrame = end;
}