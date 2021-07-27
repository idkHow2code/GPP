#include "riflebullet.h"

//=============================================================================
// default constructor
//=============================================================================
RifleBullet::RifleBullet() : Entity()
{
	spriteData.width = RiflebulletNS::WIDTH;
	spriteData.height = RiflebulletNS::HEIGHT;
	spriteData.x = RiflebulletNS::X;                   // location on screen
	spriteData.y = RiflebulletNS::Y;
	spriteData.rect.bottom = RiflebulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = RiflebulletNS::WIDTH;
	edge.left = -16;
	edge.top = -16;
	edge.right = 16;
	edge.bottom = 16;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = RiflebulletNS::RIFLEBULLET_START_FRAME;     // first frame of bullet animation
	endFrame = RiflebulletNS::RIFLEBULLET_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = RiflebulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	rifleBuffer = 12.0f;
	initialized = false;
}

bool RifleBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void RifleBullet::draw()
{
	Image::draw();              // draw bullet
}

void RifleBullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
	/*if (this->rifleBuffer != 30.0f)
	{
	rifleBuffer += 1.0f;
	}
	else if (this->rifleBuffer == 30.0f)
	rifleBuffer = 0.0f;

	if (this->rifleBuffer != 6.0f)
	{
	rifleBuffer += 1.0f;
	}
	else if (this->rifleBuffer == 6.0f)
	rifleBuffer = 0.0f;

	if (this->rifleBuffer != 60.0f)
	{
	rifleBuffer += 1.0f;
	}
	else if (this->rifleBuffer == 60.0f)
	rifleBuffer = 0.0f;

	if (this->rifleBuffer != 12.0f)
	{
	rifleBuffer += 1.0f;
	}
	else if (this->rifleBuffer == 12.0f)
	rifleBuffer = 0.0f;*/
}

void RifleBullet::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void RifleBullet::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}

