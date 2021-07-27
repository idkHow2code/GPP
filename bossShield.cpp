#include "bossShield.h"

//=============================================================================
// default constructor
//=============================================================================
BossShield::BossShield() : Entity()
{
	spriteData.width = ShieldNS::WIDTH;           // size of boss
	spriteData.height = ShieldNS::HEIGHT;
	spriteData.x = prevX;                   // location on screen
	spriteData.y = prevY;
	spriteData.rect.bottom = ShieldNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = ShieldNS::WIDTH;
	radius = ShieldNS::COLLISION_RADIUS;
	startFrame = ShieldNS::SHIELD_START_FRAME;    // first frame of ship animation
	endFrame = ShieldNS::SHIELD_END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;

}

bool BossShield::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(ShieldNS::SHIELD_START_FRAME, ShieldNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ShieldNS::SHIELD_START_FRAME);
	shield.setLoop(true);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void BossShield::draw()
{
	Image::draw();
}

void BossShield::update(float frameTime)
{
	angle = angle +0.1;
	prevX = ShieldNS::X + cos(angle)*shieldRadius;
	prevY = ShieldNS::Y + sin(angle)*shieldRadius;
	spriteData.angle += 0.1f;
}
int BossShield::getprevX()
{
	return prevX;
}

void BossShield::setprevX(int newX)
{
	prevX = newX;
}

int BossShield::getprevY()
{
	return prevY;
}

void BossShield::setprevY(int newY)
{
	prevY = newY;
}