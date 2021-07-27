#include "pistolbullet.h"

//=============================================================================
// default constructor
//=============================================================================
PistolBullet::PistolBullet() : Entity()
{
	spriteData.width = pistolbulletNS::WIDTH;
	spriteData.height = pistolbulletNS::HEIGHT;
	spriteData.x = pistolbulletNS::X;                   // location on screen
	spriteData.y = pistolbulletNS::Y;
	spriteData.rect.bottom = pistolbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = pistolbulletNS::WIDTH;
	edge.left = -16;
	edge.top = -16;
	edge.right = 16;
	edge.bottom = 16;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = pistolbulletNS::PISTOLBULLET_START_FRAME;     // first frame of bullet animation
	endFrame = pistolbulletNS::PISTOLBULLET_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = pistolbulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	pistolBuffer = 30.0f;
	smgBuffer = 6.0f;
	shotgunBuffer = 60.0f;
	rifleBuffer = 12.0f;
	initialized = false;
}

bool PistolBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void PistolBullet::draw()
{
	Image::draw();              // draw bullet
}

void PistolBullet::update(float frameTime)
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

void PistolBullet::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void PistolBullet::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}

