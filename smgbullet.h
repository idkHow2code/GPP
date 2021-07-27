#ifndef _SMGBULLET_H                 // Prevent multiple definitions if this 
#define _SMGBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace SMGbulletNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
								
	const int X = 0;
	const int Y = 0;
	const float SPEED = 200;                // 100 pixels per second
	const int   TEXTURE_COLS = 1;           // texture has 1 columns

	const int   SMGBULLET_START_FRAME = 0;     //No animation  
	const int   SMGBULLET_END_FRAME = 0;
	const int	SMG_DAMAGE = 1;
}

// inherits from Entity class
class SmgBullet : public Entity
{
private:
	float prevX;
	float prevY;

	float smgBuffer;
	bool initialized;

public:
	// constructor
	SmgBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void setPrev(float x, float y);
	void revertLocation();
	void damageMe(int damageValue) {};
	int getsmgDamage() { return SMGbulletNS::SMG_DAMAGE; };
	int getSmgBuffer() { return smgBuffer; };

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