#include "smgbullet.h"

//=============================================================================
// default constructor
//=============================================================================
SmgBullet::SmgBullet() : Entity()
{
	spriteData.width = SMGbulletNS::WIDTH;
	spriteData.height = SMGbulletNS::HEIGHT;
	spriteData.x = SMGbulletNS::X;                   // location on screen
	spriteData.y = SMGbulletNS::Y;
	spriteData.rect.bottom = SMGbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = SMGbulletNS::WIDTH;
	edge.left = -16;
	edge.top = -16;
	edge.right = 16;
	edge.bottom = 16;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = SMGbulletNS::SMGBULLET_START_FRAME;     // first frame of bullet animation
	endFrame = SMGbulletNS::SMGBULLET_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = SMGbulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;	
	smgBuffer = 6.0f;
	initialized = false;
}

bool SmgBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void SmgBullet::draw()
{
	Image::draw();              // draw bullet
}

void SmgBullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
	/*if (this->SMGBuffer != 30.0f)
	{
	SMGBuffer += 1.0f;
	}
	else if (this->SMGBuffer == 30.0f)
	SMGBuffer = 0.0f;

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

void SmgBullet::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void SmgBullet::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}

