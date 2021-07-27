// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _PLAYERHEALTH_H                 // Prevent multiple definitions if this 
#define _PLAYERHEALTH_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "dontdie.h"

namespace playerHealthNS
{
	const int WIDTH = 38;                   // image width
	const int HEIGHT = 32;                  // image height
	//const int X = ;// location on screen
	//const int Y = ;
	const float SPEED = 100;                // 100 pixels per second
	//const float MASS = 250.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   PLAYERHEALTH_START_FRAME = 0;      
	const int   PLAYERHEALTH_END_FRAME = 0;     
	//const float PLAYER_ANIMATION_DELAY = 0.2f;    // time between frames
}

class PlayerHealth : public Entity
{
public:
	// constructor
	PlayerHealth();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
};




#endif