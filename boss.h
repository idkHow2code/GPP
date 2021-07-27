#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#define _USE_MATH_DEFINES

#include "entity.h"
#include "constants.h"
#include <string>
#include "bossShield.h"
#include "bossCannon.h"
#include "player.h"
#include <vector>

namespace bossNS
{
	const int	MAXHP = 2000;
	const int	WIDTH = 128;                   // image width
	const int	HEIGHT = 128;                  // image height
	const int	X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int	Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	///////////////////////////////////////////////////////
	////////////BARON :: FORM 1////////////////////////////
	const int   BARON_START_FRAME = 0;      // boss starts at frame 0
	const int   BARON_END_FRAME = 2;        // boss animation frames 0,1,2 
	const int	BARON_CHANNEL_START_FRAME = 3;	//frame 3,4 is used for attack
	const int	BARON_CHANNEL_END_FRAME = 4;	//frame 3,4 is used for attack
	const int	BARON_ATTACK_FRAME = 5;
	const int	BARON_RELOADING_TIMER = 1;
	const int	BARON_CHANNELING_TIMER = 1;
	const int	BARON_ATTACKING_TIMER = 3;
	const float BARON_ANIMATION_DELAY = 0.5f;    // time between frames
	///////////////////////////////////////////////////////
	////////////NORAB :: FORM 2////////////////////////////
	const int   NORAB_START_FRAME = 6;      // boss starts at frame 6
	const int   NORAB_END_FRAME = 8;        // boss animation frames 6,7,8 
	const int	NORAB_CHANNEL_START_FRAME = 9;	//frame 9,10 is used for attack
	const int	NORAB_CHANNEL_END_FRAME = 10;	//frame 9,10 is used for attack
	const int	NORAB_ATTACK_FRAME = 11;
	const int	NORAB_RELOADING_TIMER = 3;
	const int	NORAB_CHANNELING_TIMER = 2;
	const int	NORAB_ATTACKING_TIMER = 2;
	const float NORAB_ANIMATION_DELAY = 0.5f;    // time between frames
	const float CHARRRGE_SPEED = 120.0f;
	///////////////////////////////////////////////////////
}

enum BOSS_STATUS {
	NotSpawn = 0,
	Reloading = 1,
	Channeling = 2,
	Attacking = 3,
	Dead = 4,
};

class Boss : public Entity
{ 
protected:
	float HP = 500;
	int form = 1;
	int damage = 1;
	bool spawn = false;
	Image boss_form; //sprite Data
	bool reloading = true;
	bool channeling = false;
	bool attacking = false;
	bool shieldOn = false; // for form 1
	bool died = false; // for win screen
	float prevX;
	float prevY;

public:
	// constructor
	Boss();
	
	//common functions
	int getDamage();
	void setDamage(int dmg);
	float getHP();
	void setHP(float hp) { this->HP = hp; }
	int getForm();
	void setForm(int fo) { this->form = fo; }
	bool isSpawn();
	void setSpawn(bool spawnVal) { this->spawn = spawnVal; }
	void takesDamage(int dmgValue);
	bool hasShield();
	bool isReloading();
	bool isChanneling();
	bool isAttacking();
	bool hasDied();
	void setDied(bool die) { this->died = die; }
	void changeMotion(bool motion);
	void setPrev(float x, float y);
	void revertLocation();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void CHARRRGE(float frameTime);

};


#endif