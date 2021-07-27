#pragma once
#ifndef _BOSSSHIELD_H                 // Prevent multiple definitions if this 
#define _BOSSSHIELD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace ShieldNS
{
	const int   WIDTH = 32;                // image width
	const int   HEIGHT = 32;               // image height
	const int   COLLISION_RADIUS = 60 / 2;   // for circular collision
	const int   SHIELD_RADIUS = 77;
	const int   X = GAME_WIDTH/2 - WIDTH/2;
	const int   Y = GAME_HEIGHT/2 - HEIGHT/2;
	const int   TEXTURE_COLS = 1;       // texture has 1 columnn
	const int   SHIELD_START_FRAME = 0;        // starts at frame 0
	const int   SHIELD_END_FRAME = 0;          // no animation
}

class BossShield : public Entity            // inherits from Entity class
{
private:
	Image shield;
	int shieldRadius = ShieldNS::SHIELD_RADIUS;
	float angle = 0;
	int prevX = ShieldNS::X+shieldRadius;
	int prevY = ShieldNS::Y;
public:
	// constructor
	BossShield();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	int getprevX();
	void setprevX(int newX);
	int getprevY();
	void setprevY(int newY);
};
#endif