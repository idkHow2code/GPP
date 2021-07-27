#include "zombie.h"

//=============================================================================
// default constructor
//=============================================================================
Zombie::Zombie() : Entity()
{
	spriteData.width = zombieNS::WIDTH;
	spriteData.height = zombieNS::HEIGHT;
	spriteData.x = zombieNS::X;                   // location on screen
	spriteData.y = zombieNS::Y;
	spriteData.rect.bottom = zombieNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = zombieNS::WIDTH;
	velocity.x =  0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = zombieNS::ZOMBIE_ANIMATION_DELAY;
	startFrame = zombieNS::ZOMBIE_START_FRAME;     // first frame of ship animation
	endFrame = zombieNS::ZOMBIE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = zombieNS::WIDTH / 2.0;
	health = zombieNS::HEALTH;
	collisionType = entityNS::CIRCLE;
	wallVector.x = 0;
	wallVector.y = 0;
	attackBuffer = 60.0f;
	initialised = false;
}

bool Zombie::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Zombie::draw()
{
	Image::draw();              // draw zombie
}

void Zombie::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
	if (this->attackBuffer != 60.0f)
	{
		attackBuffer += 1.0f;
		this->endFrame = 1;
	}
	else
	{
		this->endFrame = 0;
	}
}
void Zombie::ai(float frameTime, Zombie &ent)
{
	//spriteData.x = spriteData.x + frameTime * zombieNS::ZOMBIE_SPEED;
}
void Zombie::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void Zombie::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}
int Zombie::getDamage()
{
	if (attackBuffer == 60)
	{
		attackBuffer = 0;
		return zombieNS::DAMAGE;
	}
	else
	{
		return 0;
	}

}

void Zombie::damageZombie(int damage)
{
	this->health -= damage;
}



int Zombie::getWallVectorX()
{
	return this->wallVector.x;
}
int Zombie::getWallVectorY()
{
	return this->wallVector.y;
}
void Zombie::setWallVector(VECTOR2 vector)
{
	this->wallVector = vector;
}

float Zombie::getAttackBuffer()
{
	return this->attackBuffer;
}

void Zombie::setAttackBuffer(float attack)
{
	this->attackBuffer = attack;
}

void Zombie::setEndFrame(int end)
{
	this->endFrame = end;
}

int Zombie::getID()
{
	return this->id;
}

void Zombie::setID(int id)
{
	this->id = id;
}