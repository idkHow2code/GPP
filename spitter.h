#ifndef _SPITTER_H                 // Prevent multiple definitions if this 
#define _SPITTER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace spitterNS
{
	const int WIDTH = 20;                   // image width
	const int HEIGHT = 12;                  // image height
											//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
											//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = GAME_WIDTH / 3 - WIDTH / 2;
	const int Y = GAME_HEIGHT / 3 - WIDTH / 2;
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   SPITTER_START_FRAME = 0;       // ship starts at frame 0
	const int   SPITTER_END_FRAME = 1;         // ship animation frames 0,1,2,3
	const float SPITTER_ANIMATION_DELAY = 0.2f; // time between frames
	const int HEALTH = 20;
	const float SPITTER_SPEED = 50.0f;
	const int DAMAGE = 2;
}

// inherits from Entity class
class Spitter : public Entity
{
private:
	int id;
	Image spitter;
	float prevX;
	float prevY;
	//float playerX;
	//float playerY;
	VECTOR2 wallVector;
	float attackBuffer;
	bool initialised;

public:
	// constructor
	Spitter();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	// inherited member functions
	void update(float frameTime);
	void ai(float frameTime, Spitter &ent);
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
};
#endif

