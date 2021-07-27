#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
	spriteData.width = bulletNS::WIDTH;
	spriteData.height = bulletNS::HEIGHT;
	spriteData.x = bulletNS::X;                   // location on screen
	spriteData.y = bulletNS::Y;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	edge.left = -16;
	edge.top = -16;
	edge.right = 16;
	edge.bottom = 16;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = bulletNS::PISTOLBULLET_START_FRAME;     // first frame of bullet animation
	endFrame = bulletNS::PISTOLBULLET_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = bulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	pistolBuffer = 30.0f;
	smgBuffer = 6.0f;
	shotgunBuffer = 60.0f;
	rifleBuffer = 12.0f;
	initialized = false;
}

bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Bullet::draw()
{
	Image::draw();              // draw bullet
}

void Bullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
	/*if (this->pistolBuffer != 30.0f)
	{
		pistolBuffer += 1.0f;
	}
	else if (this->pistolBuffer == 30.0f)
		pistolBuffer = 0.0f;

	if (this->smgBuffer != 6.0f)
	{
		smgBuffer += 1.0f;
	}
	else if (this->smgBuffer == 6.0f)
		smgBuffer = 0.0f;

	if (this->shotgunBuffer != 60.0f)
	{
		smgBuffer += 1.0f;
	}
	else if (this->smgBuffer == 60.0f)
		smgBuffer = 0.0f;

	if (this->rifleBuffer != 12.0f)
	{
		rifleBuffer += 1.0f;
	}
	else if (this->rifleBuffer == 12.0f)
		rifleBuffer = 0.0f;*/
}

void Bullet::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void Bullet::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}

