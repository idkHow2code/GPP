#include "spitter.h"

//=============================================================================
// default constructor
//=============================================================================
Spitter::Spitter() : Entity()
{
	spriteData.width = spitterNS::WIDTH;
	spriteData.height = spitterNS::HEIGHT;
	spriteData.x = spitterNS::X;                   // location on screen
	spriteData.y = spitterNS::Y;
	spriteData.rect.bottom = spitterNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = spitterNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = spitterNS::SPITTER_ANIMATION_DELAY;
	startFrame = spitterNS::SPITTER_START_FRAME;     // first frame of ship animation
	endFrame = spitterNS::SPITTER_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = spitterNS::WIDTH / 2.0;
	health = spitterNS::HEALTH;
	collisionType = entityNS::CIRCLE;
	wallVector.x = 0;
	wallVector.y = 0;
	attackBuffer = 10;
}

bool Spitter::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Spitter::draw()
{
	Image::draw();              // draw zombie
}

void Spitter::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
	if (this->attackBuffer != 20.0f)
	{
		attackBuffer += 1.0f;
	}
}
void Spitter::ai(float frameTime, Spitter &ent)
{
	//spriteData.x = spriteData.x + frameTime * zombieNS::ZOMBIE_SPEED;
}
void Spitter::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void Spitter::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}
int Spitter::getDamage()
{
	if (attackBuffer == 60)
	{
		attackBuffer = 0;
		return spitterNS::DAMAGE;
	}
	else
	{
		return 0;
	}

}
int Spitter::checkVoronoiRegion(Entity &ent, VECTOR2 &collisionVector)
{
	float min01, min03, max01, max03, center01, center03;

	computeRotatedBox();                    // prepare rotated box

											// project circle center onto edge01
	center01 = graphics->Vector2Dot(&edge01, ent.getCenter());
	min01 = center01 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max01 = center01 + ent.getRadius()*ent.getScale();
	if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
		return false;                       // no collision is possible

											// project circle center onto edge03
	center03 = graphics->Vector2Dot(&edge03, ent.getCenter());
	min03 = center03 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max03 = center03 + ent.getRadius()*ent.getScale();
	if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
		return false;                       // no collision is possible

											// circle projection overlaps box projection
											// check to see if circle is in voronoi region of collision box
	if (center01 < edge01Min && center03 < edge03Min)    // if circle in Voronoi0
		return 0;
	if (center01 > edge01Max && center03 < edge03Min)    // if circle in Voronoi1
		return 1;
	if (center01 > edge01Max && center03 > edge03Max)    // if circle in Voronoi2
		return 2;
	if (center01 < edge01Min && center03 > edge03Max)    // if circle in Voronoi3
		return 3;

}


int Spitter::getWallVectorX()
{
	return this->wallVector.x;
}
int Spitter::getWallVectorY()
{
	return this->wallVector.y;
}
void Spitter::setWallVector(VECTOR2 vector)
{
	this->wallVector = vector;
}

float Spitter::getAttackBuffer()
{
	return this->attackBuffer;
}

void Spitter::setAttackBuffer(float attack)
{
	this->attackBuffer = attack;
}

void Spitter::setEndFrame(int end)
{
	this->endFrame = end;
}
int Spitter::getID()
{
	return this->id;
}

void Spitter::setID(int id)
{
	this->id = id;
}