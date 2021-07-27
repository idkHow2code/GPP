#ifndef _PISTOLBULLET_H                 // Prevent multiple definitions if this 
#define _PISTOLBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace pistolbulletNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = 0;
	const int Y = 0;
	const float SPEED = 200;                // 100 pixels per second
	const int   TEXTURE_COLS = 1;           // texture has 1 columns

	const int   PISTOLBULLET_START_FRAME = 0;     //No animation  
	const int   PISTOLBULLET_END_FRAME = 0;         
	const int	PISTOL_DAMAGE = 4;
}

// inherits from Entity class
class PistolBullet : public Entity
{
private:
	float prevX;
	float prevY;
	
	float pistolBuffer;
	float smgBuffer;
	float shotgunBuffer;
	float rifleBuffer;
	bool initialized;

public:
	// constructor
	PistolBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void setPrev(float x, float y);
	void revertLocation();
	void damageMe(int damageValue) {};
	int getpistolDamage() { return pistolbulletNS::PISTOL_DAMAGE; };
	int getPistolBuffer() { return pistolBuffer; };

	bool isInitialized()
	{
		return initialized;
	}
	void setInitialized(bool init)
	{
		initialized == init;
	}
};

#endif