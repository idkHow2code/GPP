#ifndef _SPITTERBULLET_H                 // Prevent multiple definitions if this 
#define _SPITTERBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace spitterbulletNS
{
	const int WIDTH = 7;                   // image width
	const int HEIGHT = 7;                  // image height
											//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
											//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = GAME_WIDTH / 3 - WIDTH / 2;
	const int Y = GAME_HEIGHT / 3 - WIDTH / 2;
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   SPITTERBULLET_START_FRAME = 0;       // ship starts at frame 0
	const int   SPITTERBULLET_END_FRAME = 0;         // ship animation frames 0,1,2,3
	const float SPITTERBULLET_ANIMATION_DELAY = 0.2f; // time between frames
	const int DAMAGE = 2;
	const float SPITTERBULLET_SPEED = 100.0f;
}

// inherits from Entity class
class Spitterbullet : public Entity
{
private:
	bool attack;
	Image spitterbullet;
	VECTOR2 wallVector;
	bool initialised;

public:
	// constructor
	Spitterbullet();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	// inherited member functions
	void update(float frameTime);
	void ai(float frameTime, Spitterbullet &ent);
	int getDamage();
	void setWallVector(VECTOR2 vector);
	int getWallVectorX();
	int getWallVectorY();
	void setEndFrame(int end);
	bool isInitialised()
	{
		return initialised;
	}
	void setInitialised(bool init)
	{
		this->initialised = init;
	}
};
#endif

