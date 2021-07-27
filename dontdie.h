// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.h v1.0

#ifndef _THREECS_H              // Prevent multiple definitions if this 
#define _THREECS_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

#include "textDX.h"
#include "player.h"
#include "wall.h"
#include "constants.h"
#include "zombie.h"
#include "boss.h"
#include "playerHealth.h"
#include "bullet.h"
#include "bossShield.h"
#include "bossCannon.h"
#include <vector>
#include <list>
#include "tank.h"
#include "spitter.h"
#include "spitterbullet.h"
#include <vector>
#include <string>
#include "start.h"
#include "win.h"
#include "lose.h"
#include "instruction.h"

//Background Music
//using Microsoft.DirectX.AudioVideoPlayback;
//Sound Effects
//using Microsoft.DirectX.DirectSound;
//using DS = Microsoft.DirectX.DirectSound;

namespace dontdieNS
{

	//const char FONT[] = "Arial Bold";  // font
	const int TEXTURE_SIZE = 64;
	const int TEXTURE_COLS = 5;
	const int MAP_HEIGHT = 9;
	const int MAP_WIDTH = 12;
	const float SCROLL_RATE = 10;
	const int __ = -1;                  // empty tile

	const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
		 0,1,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,1,0,
		 0,0,0,1,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,1,0,0,0,0,0,
		 0,1,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,1,0,
		 0,0,1,0,0,0,0,0,0,0,0,0
	};
}

class dontdie : public Game
{
private:
    // game items
	
	Boss boss;
	BossShield shield;
    // game items	
	float mapX;
	float mapY;
	TextureManager mapTexture;   // map texture
	TextureManager playerTexture;     // player texture
	TextureManager playerHealthTexture; 
	TextureManager wallTexture; //wall texture
	TextureManager zombieTexture;
	TextureManager bossTexture;
	TextureManager shieldTexture;
	TextureManager cannonTexture;
	TextureManager bossMAXHPTexture;
	TextureManager bossCURHPTexture;
	int fpscounter = 0;
	int seconds = 0;
	float CannonAngle = 0.0f;
	int	BARON_RELOADING_TIMER = bossNS::BARON_RELOADING_TIMER;
	int	BARON_CHANNELING_TIMER = bossNS::BARON_CHANNELING_TIMER;
	int	BARON_ATTACKING_TIMER = bossNS::BARON_ATTACKING_TIMER;
	int	NORAB_RELOADING_TIMER = bossNS::NORAB_RELOADING_TIMER;
	int	NORAB_CHANNELING_TIMER = bossNS::NORAB_CHANNELING_TIMER;
	int	NORAB_ATTACKING_TIMER = bossNS::NORAB_ATTACKING_TIMER;
	int cannonInt = 0;
	TextureManager tankTexture;
	TextureManager spitterTexture;
	TextureManager spitterbulletTexture;

	Image   map;                 // map image
	Image player;                 // player image
	TextureManager PbulletTexture;
	TextureManager SMGbulletTexture;
	TextureManager ShotgunbulletTexture;
	TextureManager RiflebulletTexture;
	Image playerhealth;
	Image zombie;
	Image	wall;				 // wall image
	Image tank;
	Image spitter;
	Image spitterbullet;
	Image bossMAXHP;
	Image bossCURHP;
	Image pistolBullet;          // pistol bullet image
	Image smgBullet;
	Image shotgunBullet;
	Image rifleBullet;

	Player player1;
    //PlayerHealth player1health;
	Bullet pistolBulletArray[100], smgBulletArray[100], shotgunBulletArray[100], rifleBulletArray[100];
	BossCannon CannonArray[64];
	Wall wallArray[10];
	Zombie zombieArray[50];
	Tank tankArray[10];
	Spitter spitterArray[10];
	Spitterbullet spitterbulletArray[500];

	float spawnbuffer;
	int spitterbulletID;
	int stage;
	bool stageSpawnComplete;
	int zombieStageOneSpawn;
	int zombieTotalInitialised;
	int tankTotalInitialised;
	int spitterTotalInitialised;
	int zombieStageTwoSpawn;
	int TankStageTwoSpawn;
	int zombieStageThreeSpawn;
	int TankStageThreeSpawn;
	int SpitterStageThreeSpawn;
	int zombieStageBossSpawn;
	int TankStageBossSpawn;
	int SpitterStageBossSpawn;
	int currentSpawn;
	float stageBufferTime;
	float clearCooldown;
	
    // game variables
	//Background Music
	/*private Audio backMusic;
	private double lastmusicposition;*/
	//Sound Effects
	/*private DS.Device sounddevice;
	private SecondaryBuffer shotsound;*/

	float pistolBuffer,smgBuffer,shotgunBuffer,rifleBuffer;
	int pBullets,smgBullets,rifleBullets;
	bool shoot = false;

	TextDX  *dxFontSmall;       // DirectX fonts
	TextDX  *dxFontMedium;
	TextDX  *dxFontLarge;

	int state;
	Start startScreen;
	TextureManager StartTexture;
	Image start;
	Win winScreen;
	Lose loseScreen;
	TextureManager WinTexture;
	TextureManager LoseTexture;

	Instruction instructionScreen;
	TextureManager InstructionTexture;
	Image instruction;

	int clickBuffer;
public:
	//Constructor
	dontdie();

	//Deconstructor
    virtual ~dontdie();

	//Initialize the game
    void initialize(HWND hwnd);
    void reset();
    void update();
	void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
	bool checkStageClear();
	void clearAllMobs();
	/*private void InitializeSound()
	{
		sounddevice = new DS.Device();
		sounddevice.SetCooperativeLevel(this, CooperativeLevel.Normal);

		BufferDescription description = new BufferDescription();
		description.ControlEffects = false;
		shotsound = new SecondaryBuffer("shot.wav", description, sounddevice);
		shotsound.Play(0, BufferPlayFlags.Default);
	}*/
};

#endif
