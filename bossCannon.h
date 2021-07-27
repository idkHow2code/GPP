#pragma once
#ifndef _BOSSCANNON_H                 // Prevent multiple definitions if this 
#define _BOSSCANNON_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>


namespace Cannon
{
	const int   WIDTH = 16;                // image width
	const int   HEIGHT = 16;               // image height
	const int   COLLISION_RADIUS = 16 / 2;   // for circular collision
	const int   X = GAME_WIDTH/2 -WIDTH/2;
	const int   Y = GAME_HEIGHT/2-70;
	const int   TEXTURE_COLS = 2;       // texture has 2 columns
	const int   CANNON_START_FRAME = 0;        // starts at frame 0
	const int   CANNON_END_FRAME = 1;          // ends at frame 1
	const float CANNON_ANIMATION_DELAY = 0.5f;    // time between frames
}

class BossCannon : public Entity            // inherits from Entity class
{
private:
	int damage = 1;
	Image CannonBall;
	bool initialised = false;
public:
	// constructor
	BossCannon();

	int getdamage();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void setVelocityX(float newX);
	void setVelocityY(float newY);
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