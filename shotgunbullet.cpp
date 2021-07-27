#include "shotgunbullet.h"

//=============================================================================
// default constructor
//=============================================================================
ShotgunBullet::ShotgunBullet() : Entity()
{
	spriteData.width = ShotgunbulletNS::WIDTH;
	spriteData.height = ShotgunbulletNS::HEIGHT;
	spriteData.x = ShotgunbulletNS::X;                   // location on screen
	spriteData.y = ShotgunbulletNS::Y;
	spriteData.rect.bottom = ShotgunbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = ShotgunbulletNS::WIDTH;
	edge.left = -16;
	edge.top = -16;
	edge.right = 16;
	edge.bottom = 16;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = ShotgunbulletNS::SHOTGUNBULLET_START_FRAME;     // first frame of bullet animation
	endFrame = ShotgunbulletNS::SHOTGUNBULLET_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = ShotgunbulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	shotgunBuffer = 60.0f;
	initialized = false;
}

bool ShotgunBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void ShotgunBullet::draw()
{
	Image::draw();              // draw bullet
}

void ShotgunBullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
	/*if (this->shotgunBuffer != 30.0f)
	{
	shotgunBuffer += 1.0f;
	}
	else if (this->shotgunBuffer == 30.0f)
	shotgunBuffer = 0.0f;

	if (this->shotgunBuffer != 6.0f)
	{
	shotgunBuffer += 1.0f;
	}
	else if (this->shotgunBuffer == 6.0f)
	shotgunBuffer = 0.0f;

	if (this->shotgunBuffer != 60.0f)
	{
	shotgunBuffer += 1.0f;
	}
	else if (this->shotgunBuffer == 60.0f)
	shotgunBuffer = 0.0f;

	if (this->rifleBuffer != 12.0f)
	{
	rifleBuffer += 1.0f;
	}
	else if (this->rifleBuffer == 12.0f)
	rifleBuffer = 0.0f;*/
}

void ShotgunBullet::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void ShotgunBullet::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}

