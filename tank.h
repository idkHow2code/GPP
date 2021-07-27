#ifndef _TANK_H                 // Prevent multiple definitions if this 
#define _TANK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace tankNS
{
	const int WIDTH = 38;                   // image width
	const int HEIGHT = 26;                  // image height
											//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
											//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = GAME_WIDTH / 3 - WIDTH / 2;
	const int Y = GAME_HEIGHT / 3 - WIDTH / 2;
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   TANK_START_FRAME = 0;       // ship starts at frame 0
	const int   TANK_END_FRAME = 0;         // ship animation frames 0,1,2,3
	const float TANK_ANIMATION_DELAY = 0.2f; // time between frames
	const int DAMAGE = 2;
	const int HEALTH = 20;
	const float TANK_SPEED = 20.0f;
}

// inherits from Entity class
class Tank : public Entity
{
private:
	int id;
	Image tank;
	float prevX;
	float prevY;
	//float playerX;
	//float playerY;
	VECTOR2 wallVector;
	float attackBuffer;
	bool initialised;
	float damageAnimationBuffer;

public:
	// constructor
	Tank();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	// inherited member functions
	void update(float frameTime);
	void ai(float frameTime, Tank &ent);
	void setPrev(float x, float y);
	void revertLocation();
	int getDamage();
	//void setPlayerLoc(float x, float y) { playerX = x; playerY = y; };
	int checkVoronoiRegion(Entity &ent, VECTOR2 &collisionVector);
	void setWallVector(VECTOR2 vector);
	int getWallVectorX();
	int getWallVectorY();
	void setAttackBuffer(float buffer);
	float getAttackBuffer();
	void setStartFrame(int end) { this->startFrame = end; }
	void setEndFrame(int end); 
	int getID();
	void setID(int id);
	bool isInitialised()
	{
		return this->initialised;
	}
	void setInitialised(bool init)
	{
		this->initialised = init;
	}
	void setDamageAnimationBuffer(float inte)
	{
		this->damageAnimationBuffer = inte;
	}
	float getDamageAnimationBuffer()
	{
		return this->damageAnimationBuffer;
	}
};
#endif

