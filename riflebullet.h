#ifndef _RIFLEBULLET_H                 // Prevent multiple definitions if this 
#define _RIFLEBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace RiflebulletNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
											//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
											//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = 0;
	const int Y = 0;
	const float SPEED = 200;                // 100 pixels per second
	const int   TEXTURE_COLS = 1;           // texture has 1 columns

	const int   RIFLEBULLET_START_FRAME = 0;     //No animation  
	const int   RIFLEBULLET_END_FRAME = 0;
	const int	RIFLE_DAMAGE = 1;
}

// inherits from Entity class
class RifleBullet : public Entity
{
private:
	float prevX;
	float prevY;

	float rifleBuffer;
	bool initialized;

public:
	// constructor
	RifleBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void setPrev(float x, float y);
	void revertLocation();
	void damageMe(int damageValue) {};
	int getrifleDamage() { return RiflebulletNS::RIFLE_DAMAGE; };
	int getrifleBuffer() { return rifleBuffer; };

	bool isInitialized()
	{
		return initialized;
	}
	void setInitialized(bool init)
	{
		this->initialized == init;
	}
};

#endif