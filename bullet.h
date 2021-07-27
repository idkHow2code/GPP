#ifndef _PISTOLBULLET_H                 // Prevent multiple definitions if this 
#define _PISTOLBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height

	//const int pistolWidth = 7;
	//const int pistolHeight = 7;
	//const int shotgunWidth = 9;
	//const int shotgunHeight = 12;
	//const int smgWidth = 3;
	//const int smgHeight = 5;
	//const int rifleWidth = 5;
	//const int rifleHeight = 11;
	//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = 0;
	const int Y = 0;
	const float SPEED = 200;                // 100 pixels per second
	const int   TEXTURE_COLS = 1;           // texture has 1 columns

	const int   PISTOLBULLET_START_FRAME = 0;     //No animation  
	const int   PISTOLBULLET_END_FRAME = 0;         
	const int	PISTOL_DAMAGE = 4;
	
	const int   SMGBULLET_START_FRAME = 3;     //No animation  
	const int   SMGBULLET_END_FRAME = 3;
	const int	SMG_DAMAGE = 1;

	const int   SHOTGUNBULLET_START_FRAME = 1;     //No animation  
	const int   SHOTGUNBULLET_END_FRAME = 1;
	const int	SHOTGUN_DAMAGE = 4;

	const int   RIFLEBULLET_START_FRAME = 2;     //No animation  
	const int   RIFLEBULLET_END_FRAME = 2;
	const int	RIFLE_DAMAGE = 4;
}

// inherits from Entity class
class Bullet : public Entity
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
	Bullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void setPrev(float x, float y);
	void revertLocation();
	void damageMe(int damageValue) {};
	int getpistolDamage() { return bulletNS::PISTOL_DAMAGE; };
	int getsmgDamage() { return bulletNS::SMG_DAMAGE; };
	int getshotgunDamage() { return bulletNS::SHOTGUN_DAMAGE; };
	int getrifleDamage() { return bulletNS::RIFLE_DAMAGE; };
	int getPistolBuffer() { return pistolBuffer; };
	int getSmgBuffer() { return smgBuffer; };
	int getShotgunBuffer() { return shotgunBuffer; };
	int getRifleBuffer() { return rifleBuffer; };

	bool isInitialized()
	{
		return initialized;
	}
	void setInitialized(bool init)
	{
		this->initialized = init;
	}
};

#endif