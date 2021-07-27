// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _WALL_H               // Prevent multiple definitions if this 
#define _WALL_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace wallNS
{
	const int   WIDTH = 64;                // image width
	const int   HEIGHT = 24;               // image height
	const int   COLLISION_RADIUS = 120 / 2;   // for circular collision
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float MASS = 1.0e14f;         // mass
	const int   TEXTURE_COLS = 1;       // texture has 1 columns
	const int WALL_HEIGHT = 16;            
	const int WALL_WIDTH = 16;
	const int   START_FRAME = 0;        // starts at frame 1
	const int   END_FRAME = 0;          // no animation

	//const int __ = -1;                  // empty tile

	//const int wallSpace[WALL_HEIGHT][WALL_WIDTH] = {
	//	__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
	//	__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__,
	//	__,__,__,__,__, 1,__,__,__,__,__,__, 1, 1, 1, 1,
	//	__,__,__,__,__, 1,__,__,__,__,__,__,__,__,__,__,
	//	__,__,__,__,__, 1, 1, 1, 1, 1,__,__,__,__,__,__,
	//	__,__,__,__,__,__,__,__,__,__,__,__,__, 1,__,__,
	//	__,__,__,__,__,__,__,__,__,__,__,__,__, 1,__,__,
	//	 1, 1, 1, 1, 1, 1,__,__,__,__,__,__,__, 1,__,__,
	//	__,__,__,__,__,__,__,__,__,__,__,__,__, 1,__,__,
	//	__,__,__,__,__,__,__,__,__,__,__,__,__, 1,__,__,
	//	__,__,__,__,__,__,__,__, 1,__,__,__,__, __,__,__,
	//	__,__,__,__,__,__,__,__, 1,__,__,__,__, __,__,__,
	//	__,__, 1, 1, 1, 1, 1, 1, 1,__,__,__,__,__,__,__,
	//	__,__, 1,__,__,__,__,__,__,__,__,__,__,__,__,__,
	//	__,__, 1,__,__,__,__,__,__,__,__,__,__,__,__,__,
	//	__,__, 1,__,__,__,__,__,__,__,__,__,__,__,__,__,
	//};
}

class Wall : public Entity            // inherits from Entity class
{
public:
	// constructor
	Wall();
	int checkVoronoiRegion(Entity &ent, VECTOR2 &collisionVector);
};
#endif

