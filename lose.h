#pragma once
#ifndef _LOSE_H                 // Prevent multiple definitions if this 
#define _LOSE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace LoseNS
{
	const int WIDTH = GAME_WIDTH;                   // image width
	const int HEIGHT = GAME_HEIGHT;                  // image height
													 //const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
													 //const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = 0;
	const int Y = 0;
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   LOSE_START_FRAME = 0;       // ship starts at frame 0
	const int   LOSE_END_FRAME = 4;        // ship animation frames 0,1,2,3
	const float LOSE_ANIMATION_DELAY = 1.0f; // time between frames
}

// inherits from Entity class
class Lose : public Entity
{
private:
	bool initialised;
public:
	// constructor
	Lose();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	// inherited member functions
	void update(float frameTime);
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

