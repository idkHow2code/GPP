
#include "dontdie.h"
#include "input.h"
#include "wall.h"
#include <string>
#include "astar.h"
#include "zombie.h"

using namespace dontdieNS;
//Sound Music
//using Microsoft.DirectX.DirectSound;
//using DS = Microsoft.DirectX.DirectSound;

//=============================================================================
// Constructor
//=============================================================================
dontdie::dontdie()
{
	mapX = 0;
	mapY = 0;
	dxFontSmall = new TextDX();     // DirectX fonts
	dxFontMedium = new TextDX();
	dxFontLarge = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
dontdie::~dontdie()
{
	releaseAll();               // call deviceLost() for every graphics item
	SAFE_DELETE(dxFontSmall);
	SAFE_DELETE(dxFontMedium);
	SAFE_DELETE(dxFontLarge)
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void dontdie::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	//backMusic = new Audio("music.mp3");
	//backMusic.Play();
	//ASTAR Algorithm MAP generation
	this->spitterbulletID = 0;
	this->spawnbuffer = 30;
	this->stage = 0;
	this->zombieStageOneSpawn = 50;
	this->zombieStageTwoSpawn = 45;
	this->TankStageTwoSpawn = 5;
	this->zombieStageThreeSpawn = 35;
	this->TankStageThreeSpawn = 5;
	this->SpitterStageThreeSpawn = 10;
	this->zombieStageBossSpawn = 20;
	this->TankStageBossSpawn = 8;
	this->SpitterStageBossSpawn = 5;
	this->currentSpawn = 0;
	this->stageSpawnComplete = false;
	this->stageBufferTime = 180;
	this->clearCooldown = 180;
	this->pistolBuffer = 0;
	this->smgBuffer = 0;
	this->shotgunBuffer = 0;
	this->rifleBuffer = 0;
	this->pBullets = 10000;
	this->smgBullets = 100000;
	this->rifleBullets = 10000;
	this->state = 0;
	this->clickBuffer = 30;
	player1.setX(GAME_WIDTH / 2);
	player1.setY(GAME_HEIGHT / 2);
	
	// 15 pixel high Arial
	if (dxFontSmall->initialize(graphics, 15, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// 62 pixel high Arial
	if (dxFontMedium->initialize(graphics, 62, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// 124 pixel high Arial
	if (dxFontLarge->initialize(graphics, 124, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));


	// Map texture
	if (!mapTexture.initialize(graphics, MAP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Map texture"));
	//Wall texture

	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wall texture"));
	// Player texture
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player texture"));
	if (!playerHealthTexture.initialize(graphics, HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player Health texture"));
	// Zombie Texture
	if (!zombieTexture.initialize(graphics, ZOMBIE_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Zombie texture"));
	}
	if (!PbulletTexture.initialize(graphics, BULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	}
	if (!StartTexture.initialize(graphics, START_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing start texture"));
	}
	if (!InstructionTexture.initialize(graphics, INSTRUCTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction texture"));
	if (!WinTexture.initialize(graphics, WIN_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing win texture"));
	}
	if (!LoseTexture.initialize(graphics, LOSE_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lose texture"));
	}
	if (!tankTexture.initialize(graphics, TANK_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Tank texture"));
	}
	if (!spitterTexture.initialize(graphics, SPITTER_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Spitter texture"));
	}
	if (!spitterbulletTexture.initialize(graphics, SPITTERBULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Spitter bullet texture"));
	}

	// Map 
	// Map 
	if (!startScreen.initialize(this, startNS::WIDTH, startNS::HEIGHT, startNS::TEXTURE_COLS, &StartTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing start"));
	if (!instructionScreen.initialize(this, instructionNS::WIDTH, instructionNS::HEIGHT, instructionNS::TEXTURE_COLS, &InstructionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction"));
	if (!winScreen.initialize(this, WinNS::WIDTH, WinNS::HEIGHT, WinNS::TEXTURE_COLS, &WinTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing win"));
	if (!loseScreen.initialize(this, LoseNS::WIDTH, LoseNS::HEIGHT, LoseNS::TEXTURE_COLS, &LoseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lose"));
	if (!map.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));
	map.setFrames(0, 0);
	map.setCurrentFrame(0);
	 
	// Wall 
	if (!wallArray[0].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[0].setX(GAME_WIDTH / 2);
	wallArray[0].setY(GAME_HEIGHT / 4 - 128);

	if (!wallArray[1].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[1].setX(wallArray[0].getX() + 128);
	wallArray[1].setY(GAME_HEIGHT / 4 - 64);
	//wallArray[1].setDegrees(90.0f);

	if (!wallArray[2].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[2].setX(wallArray[0].getX() - 128);
	wallArray[2].setY(GAME_HEIGHT / 4 - 64);
	//wallArray[2].setDegrees(90.0f);

	if (!wallArray[3].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[3].setX(wallArray[2].getX() - 128);
	wallArray[3].setY(GAME_HEIGHT / 4);


	if (!wallArray[4].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[4].setX(wallArray[1].getX() + 128);
	wallArray[4].setY(GAME_HEIGHT / 4);

	if (!wallArray[5].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[5].setX(GAME_WIDTH / 2);
	wallArray[5].setY(GAME_HEIGHT / 2 + 128+64);

	if (!wallArray[6].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[6].setX(wallArray[0].getX() + 128);
	wallArray[6].setY(GAME_HEIGHT / 2 + 128);
	//wallArray[6].setDegrees(90.0f);

	if (!wallArray[7].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[7].setX(wallArray[0].getX() - 128);
	wallArray[7].setY(GAME_HEIGHT / 2 + 128);
	//wallArray[7].setDegrees(90.0f);

	if (!wallArray[8].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[8].setX(wallArray[2].getX() - 128);
	wallArray[8].setY(GAME_HEIGHT / 2 + 64);

	if (!wallArray[9].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[9].setX(wallArray[1].getX() + 128);
	wallArray[9].setY(GAME_HEIGHT / 2 + 64);



	// Player
	if (!player1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
	player1.setCurrentFrame(playerNS::PLAYER_START_FRAME);
	player1.setFrameDelay(playerNS::PLAYER_ANIMATION_DELAY);
	//player1.setDegrees((atan2(player1.getY - input->getMouseY() , player1.getX - input->getMouseX()) * 180) / PI);     //angle of player
	if (!playerhealth.initialize(graphics, playerHealthNS::WIDTH, playerHealthNS::HEIGHT, playerHealthNS::TEXTURE_COLS, &playerHealthTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));


	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (!zombieArray[zomb].initialize(this, zombieNS::WIDTH, zombieNS::HEIGHT, zombieNS::TEXTURE_COLS, &zombieTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie texture"));
		}
		zombieArray[zomb].setInitialised(false);
	}
	for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
	{
		if (!pistolBulletArray[pistolb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Pistol Buller"));
		}
		pistolBulletArray[pistolb].setFrames(bulletNS::PISTOLBULLET_START_FRAME, bulletNS::PISTOLBULLET_END_FRAME);
		pistolBulletArray[pistolb].setCurrentFrame(bulletNS::PISTOLBULLET_START_FRAME);
		pistolBulletArray[pistolb].setInitialized(false);
	}

	for (int smgb = 0; smgb < (sizeof(smgBulletArray) / sizeof(*smgBulletArray)); smgb++)
	{
		if (!smgBulletArray[smgb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SMG Bullet"));
		}
		smgBulletArray[smgb].setFrames(bulletNS::SMGBULLET_START_FRAME, bulletNS::SMGBULLET_END_FRAME);
		smgBulletArray[smgb].setCurrentFrame(bulletNS::SMGBULLET_START_FRAME);
		smgBulletArray[smgb].setInitialized(false);
	}


	for (int shotgunb = 0; shotgunb < (sizeof(shotgunBulletArray) / sizeof(*shotgunBulletArray)); shotgunb++)
	{
		if (!shotgunBulletArray[shotgunb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shotgun Bullet"));
		}
		shotgunBulletArray[shotgunb].setFrames(bulletNS::SHOTGUNBULLET_START_FRAME, bulletNS::SHOTGUNBULLET_END_FRAME);
		shotgunBulletArray[shotgunb].setCurrentFrame(bulletNS::SHOTGUNBULLET_START_FRAME);
		shotgunBulletArray[shotgunb].setInitialized(false);
	}

	for (int rifleb = 0; rifleb < (sizeof(rifleBulletArray) / sizeof(*rifleBulletArray)); rifleb++)
	{
		if (!rifleBulletArray[rifleb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Pistol Buller"));
		}
		rifleBulletArray[rifleb].setFrames(bulletNS::RIFLEBULLET_START_FRAME, bulletNS::RIFLEBULLET_END_FRAME);
		rifleBulletArray[rifleb].setCurrentFrame(bulletNS::RIFLEBULLET_START_FRAME);
		rifleBulletArray[rifleb].setInitialized(false);
	}
	///////////////
	//BOSS HP BAR//
	///////////////
	if (!bossMAXHPTexture.initialize(graphics, BOSS_MAX_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss MAX HP texture"));
	if (!bossMAXHP.initialize(graphics, 500, 0, 0, &bossMAXHPTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss MAX HP BAR"));
	bossMAXHP.setX(110); //centerize the HP bar
	bossMAXHP.setY(GAME_HEIGHT - 32); //show the HP bar at the bottom
									  // BOSS
	if (!bossTexture.initialize(graphics, BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 1 texture"));
	if (!boss.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));
	// CANNON
	if (!cannonTexture.initialize(graphics, BOSSCANNON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannon texture"));
	for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
	{
		if (!CannonArray[cannonNo].initialize(this, Cannon::WIDTH, Cannon::HEIGHT, Cannon::TEXTURE_COLS, &cannonTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cannon textures"));
		}
		CannonArray[cannonNo].setInitialised(false);
		CannonArray[cannonNo].setX(Cannon::X);
		CannonArray[cannonNo].setY(Cannon::Y);
	}

	// SHIELD
	if (!shieldTexture.initialize(graphics, BOSS_SHIELD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shield texture"));
	if (!shield.initialize(this, ShieldNS::WIDTH, ShieldNS::HEIGHT, ShieldNS::TEXTURE_COLS, &shieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield"));
	shield.setFrames(ShieldNS::SHIELD_START_FRAME, ShieldNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ShieldNS::SHIELD_START_FRAME);
	shield.setX(shield.getprevX());
	shield.setY(shield.getprevY());
	//zombieArray[0].setInitialised(true);
	//zombieArray[0].setX(500);
	//zombieArray[0].setY(500);
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (!tankArray[tank].initialize(this, tankNS::WIDTH, tankNS::HEIGHT, tankNS::TEXTURE_COLS, &tankTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));
		}
		tankArray[tank].setInitialised(false);
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (!spitterArray[spitter].initialize(this, spitterNS::WIDTH, spitterNS::HEIGHT, spitterNS::TEXTURE_COLS, &spitterTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spitter texture"));
		}
		spitterArray[spitter].setInitialised(false);
	}
	for (int spitterb = 0; spitterb < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterb++)
	{
		if (!spitterbulletArray[spitterb].initialize(this, spitterbulletNS::WIDTH, spitterbulletNS::HEIGHT, spitterbulletNS::TEXTURE_COLS, &spitterbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spitter bullet texture"));
		}
		spitterbulletArray[spitterb].setInitialised(false);
	}

	boss.setSpawn(false);



	reset();            // reset all game variables
	return;
}

//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void dontdie::reset()
{
	return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void dontdie::update()
{
	//Background Music
	audio->playCue(BM_MUSIC);
	if (state == 0)
	{
		startScreen.update(frameTime);
		if (this->clickBuffer != 30) {
			this->clickBuffer += 1;
		}
		if (input->getMouseLButton() == true && this->clickBuffer == 30)
		{
			state = 1;
			startScreen.setInitialised(false);
			this->clickBuffer = 0;
		}

	}
	else if (state == 1)
	{
		instructionScreen.update(frameTime);
		if (this->clickBuffer != 30) {
			this->clickBuffer += 1;
		}
		if (input->getMouseLButton() == true && this->clickBuffer == 30)
		{
			state = 2;
			instructionScreen.setInitialised(false);
		}
	}
	else if (state == 2)
	{
		fpscounter++; //keep track of fps
		VECTOR2 dir;
		int currenthp;
		int frame;
		player1.setPrev(player1.getX(), player1.getY());
		currenthp = player1.getHealth();
		frame = 20 - currenthp;
		playerhealth.setFrames(frame, frame);
		playerhealth.setCurrentFrame(frame);
		playerhealth.setX(0);
		playerhealth.setY(0);
		playerhealth.update(frameTime);

		for (int bullet = 0; bullet < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); bullet++)
		{
			if (pistolBulletArray[bullet].isInitialized() == true)
			{
				pistolBulletArray[bullet].update(frameTime);
			}
		}
		for (int bullet = 0; bullet < (sizeof(smgBulletArray) / sizeof(*smgBulletArray)); bullet++)
		{
			if (smgBulletArray[bullet].isInitialized() == true)
			{
				smgBulletArray[bullet].update(frameTime);
			}
		}

		for (int bullet = 0; bullet < (sizeof(shotgunBulletArray) / sizeof(*shotgunBulletArray)); bullet++)
		{
			if (shotgunBulletArray[bullet].isInitialized() == true)
			{
				shotgunBulletArray[bullet].update(frameTime);
			}
		}

		for (int bullet = 0; bullet < (sizeof(rifleBulletArray) / sizeof(*rifleBulletArray)); bullet++)
		{
			if (rifleBulletArray[bullet].isInitialized() == true)
			{
				rifleBulletArray[bullet].update(frameTime);
			}
		}

		if (input->getMouseLButton() == true)
		{		
			float clickY = input->getMouseY();
			float clickX = input->getMouseX();
			//if (stage == 1)
			//{ 
			if (player1.getPistolBuffer() == 30.0f)
			{
				audio->stopCue(GUN_SHOT);
				audio->playCue(GUN_SHOT);			
				player1.setPistolBuffer(0);
				for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
				{
					if (pistolBulletArray[pistolb].isInitialized() == false)
					{
						pistolBulletArray[pistolb].setInitialized(true);
						dir.x = clickX - player1.getX();
						dir.y = clickY - player1.getY();
						float hyp = sqrt(dir.x*dir.x + dir.y*dir.y);
						dir.x /= hyp;
						dir.y /= hyp;
						dir.x *= bulletNS::SPEED;
						dir.y *= bulletNS::SPEED;
						pistolBulletArray[pistolb].setX(player1.getX());
						pistolBulletArray[pistolb].setY(player1.getY());
						pistolBulletArray[pistolb].setVelocity(dir);
						break;
					}
				}
				
			}


		

		}


		if (player1.getHp() <= 0)
		{
			if (!player1.isDead()) //if false
			{
				player1.hasDied(); //makes died true
				loseScreen.setInitialised(true);
				state = 3;
			}
		
			//player1.setHealth(20.0f);
			//player1.setY(GAME_HEIGHT / 2);
		}
		player1.update(frameTime);
		//zombie1.setPlayerLoc(player1.getX(), player1.getY());
		for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
		{
			if (zombieArray[zomb].isInitialised() == true)
			{
				zombieArray[zomb].setPrev(zombieArray[zomb].getX(), zombieArray[zomb].getY());
				zombieArray[zomb].update(frameTime);
			}
		}
		for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
		{
			if (tankArray[tank].isInitialised() == true)
			{
				tankArray[tank].setPrev(tankArray[tank].getX(), tankArray[tank].getY());
				tankArray[tank].update(frameTime);
			}
		}
		for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
		{
			if (spitterArray[spitter].isInitialised() == true)
			{
				spitterArray[spitter].setPrev(spitterArray[spitter].getX(), spitterArray[spitter].getY());
				spitterArray[spitter].update(frameTime);
			}
		}
		for (int spitterb = 0; spitterb < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterb++)
		{
			if (spitterbulletArray[spitterb].isInitialised() == true)
			{
				spitterbulletArray[spitterb].update(frameTime);
			}
		}



		for (int i = 0; i < 10; i++)
		{
			wallArray[i].update(frameTime);
		}
		if (clearCooldown != 180)
		{
			clearCooldown += 1;
		}
		if (input->isKeyDown(KILL_ALL))
		{
			if (clearCooldown == 180)
			{
				clearAllMobs();
				clearCooldown = 0;
			}

		}
		else if (input->isKeyDown(BOSS_STAGE1)) //cheat code stage 1
		{
			stage = 4;
			boss.setHP(bossNS::MAXHP);
			boss.setX(bossNS::X); //reset position
			boss.setY(bossNS::Y);
		}
		else if (input->isKeyDown(BOSS_STAGE2)) //cheat code stage 2
		{
			stage = 4;
			boss.setHP(bossNS::MAXHP / 2);
			boss.setX(bossNS::X); //reset position
			boss.setY(bossNS::Y);
		}
		if (checkStageClear() == true)
		{
			stage += 1;
			stageSpawnComplete = false;
			spawnbuffer = 30;
			currentSpawn = 0;
		}
		if (stage == 1)
		{
			if (spawnbuffer == 30)
			{
				if (stageSpawnComplete == false)
				{
					if (zombieStageOneSpawn != 0)
					{

						zombieArray[zombieStageOneSpawn - 1].setInitialised(true);
						zombieArray[zombieStageOneSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							zombieArray[zombieStageOneSpawn - 1].setX(0 + zombieArray[zombieStageOneSpawn - 1].getWidth());
							zombieArray[zombieStageOneSpawn - 1].setY(0 + zombieArray[zombieStageOneSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							zombieArray[zombieStageOneSpawn - 1].setX(0 + zombieArray[zombieStageOneSpawn - 1].getWidth());
							zombieArray[zombieStageOneSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageOneSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							zombieArray[zombieStageOneSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageOneSpawn - 1].getWidth());
							zombieArray[zombieStageOneSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageOneSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							zombieArray[zombieStageOneSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageOneSpawn - 1].getWidth());
							zombieArray[zombieStageOneSpawn - 1].setY(0 + zombieArray[zombieStageOneSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						zombieStageOneSpawn -= 1;
					}
					else
					{
						stageSpawnComplete = true;
					}
				}
			}
			else
			{
				spawnbuffer += 1;
			}
		}
		if (stage == 2)
		{
			if (spawnbuffer == 30)
			{
				if (stageSpawnComplete == false)
				{
					if (zombieStageTwoSpawn != 0)
					{
						zombieArray[zombieStageTwoSpawn - 1].setInitialised(true);
						zombieArray[zombieStageTwoSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							zombieArray[zombieStageTwoSpawn - 1].setX(0 + zombieArray[zombieStageTwoSpawn - 1].getWidth());
							zombieArray[zombieStageTwoSpawn - 1].setY(0 + zombieArray[zombieStageTwoSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							zombieArray[zombieStageTwoSpawn - 1].setX(0 + zombieArray[zombieStageTwoSpawn - 1].getWidth());
							zombieArray[zombieStageTwoSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageTwoSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							zombieArray[zombieStageTwoSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageTwoSpawn - 1].getWidth());
							zombieArray[zombieStageTwoSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageTwoSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							zombieArray[zombieStageTwoSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageTwoSpawn - 1].getWidth());
							zombieArray[zombieStageTwoSpawn - 1].setY(0 + zombieArray[zombieStageTwoSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						zombieStageTwoSpawn -= 1;

					}
					else if (TankStageTwoSpawn != 0)
					{

						tankArray[TankStageTwoSpawn - 1].setInitialised(true);
						tankArray[TankStageTwoSpawn - 1].setStartFrame(0);
						tankArray[TankStageTwoSpawn - 1].setEndFrame(0);
						tankArray[TankStageTwoSpawn - 1].setHealth(5);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							tankArray[TankStageTwoSpawn - 1].setX(0 + tankArray[TankStageTwoSpawn - 1].getWidth());
							tankArray[TankStageTwoSpawn - 1].setY(0 + tankArray[TankStageTwoSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							tankArray[TankStageTwoSpawn - 1].setX(0 + tankArray[TankStageTwoSpawn - 1].getWidth());
							tankArray[TankStageTwoSpawn - 1].setY(GAME_HEIGHT - tankArray[TankStageTwoSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							tankArray[TankStageTwoSpawn - 1].setX(GAME_WIDTH - tankArray[TankStageTwoSpawn - 1].getWidth());
							tankArray[TankStageTwoSpawn - 1].setY(GAME_HEIGHT - tankArray[TankStageTwoSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							tankArray[TankStageTwoSpawn - 1].setX(GAME_WIDTH - tankArray[TankStageTwoSpawn - 1].getWidth());
							tankArray[TankStageTwoSpawn - 1].setY(0 + tankArray[TankStageTwoSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						TankStageTwoSpawn -= 1;
					}
					else
					{
						stageSpawnComplete = true;
					}

				}
			}
			else
			{
				spawnbuffer += 1;
			}
		}
		else if (stage == 3)
		{
			if (spawnbuffer == 30)
			{
				if (stageSpawnComplete == false)
				{
					if (zombieStageThreeSpawn != 0)
					{

						zombieArray[zombieStageThreeSpawn - 1].setInitialised(true);
						zombieArray[zombieStageThreeSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							zombieArray[zombieStageThreeSpawn - 1].setX(0 + zombieArray[zombieStageThreeSpawn - 1].getWidth());
							zombieArray[zombieStageThreeSpawn - 1].setY(0 + zombieArray[zombieStageThreeSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							zombieArray[zombieStageThreeSpawn - 1].setX(0 + zombieArray[zombieStageThreeSpawn - 1].getWidth());
							zombieArray[zombieStageThreeSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageThreeSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							zombieArray[zombieStageThreeSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageThreeSpawn - 1].getWidth());
							zombieArray[zombieStageThreeSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageThreeSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							zombieArray[zombieStageThreeSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageThreeSpawn - 1].getWidth());
							zombieArray[zombieStageThreeSpawn - 1].setY(0 + zombieArray[zombieStageThreeSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						zombieStageThreeSpawn -= 1;
					}
					else if (TankStageThreeSpawn != 0)
					{

						tankArray[TankStageThreeSpawn - 1].setInitialised(true);
						tankArray[TankStageThreeSpawn - 1].setStartFrame(0);
						tankArray[TankStageThreeSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							tankArray[TankStageThreeSpawn - 1].setX(0 + tankArray[TankStageThreeSpawn - 1].getWidth());
							tankArray[TankStageThreeSpawn - 1].setY(0 + tankArray[TankStageThreeSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							tankArray[TankStageThreeSpawn - 1].setX(0 + tankArray[TankStageThreeSpawn - 1].getWidth());
							tankArray[TankStageThreeSpawn - 1].setY(GAME_HEIGHT - tankArray[TankStageThreeSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							tankArray[TankStageThreeSpawn - 1].setX(GAME_WIDTH - tankArray[TankStageThreeSpawn - 1].getWidth());
							tankArray[TankStageThreeSpawn - 1].setY(GAME_HEIGHT - tankArray[TankStageThreeSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							tankArray[TankStageThreeSpawn - 1].setX(GAME_WIDTH - tankArray[TankStageThreeSpawn - 1].getWidth());
							tankArray[TankStageThreeSpawn - 1].setY(0 + tankArray[TankStageThreeSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						TankStageThreeSpawn -= 1;
					}
					else if (SpitterStageThreeSpawn != 0)
					{

						spitterArray[SpitterStageThreeSpawn - 1].setInitialised(true);
						spitterArray[SpitterStageThreeSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							spitterArray[SpitterStageThreeSpawn - 1].setX(0 + spitterArray[SpitterStageThreeSpawn - 1].getWidth());
							spitterArray[SpitterStageThreeSpawn - 1].setY(0 + spitterArray[SpitterStageThreeSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							spitterArray[SpitterStageThreeSpawn - 1].setX(0 + spitterArray[SpitterStageThreeSpawn - 1].getWidth());
							spitterArray[SpitterStageThreeSpawn - 1].setY(GAME_HEIGHT - spitterArray[SpitterStageThreeSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							spitterArray[SpitterStageThreeSpawn - 1].setX(GAME_WIDTH - spitterArray[SpitterStageThreeSpawn - 1].getWidth());
							spitterArray[SpitterStageThreeSpawn - 1].setY(GAME_HEIGHT - spitterArray[SpitterStageThreeSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							spitterArray[SpitterStageThreeSpawn - 1].setX(GAME_WIDTH - spitterArray[SpitterStageThreeSpawn - 1].getWidth());
							spitterArray[SpitterStageThreeSpawn - 1].setY(0 + spitterArray[SpitterStageThreeSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						SpitterStageThreeSpawn -= 1;
					}
					else
					{
						stageSpawnComplete = true;
					}
				}
			}
			else
			{
				spawnbuffer += 1;
			}
		}
		else if (stage == 4)
		{
			if (!boss.getActive())
			{
				boss.setActive(true);
				boss.setSpawn(true);
			}
			///////////////////////////////////////////////////////////////////////////////
			////////////////////Mobs spawn/////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////
			if (spawnbuffer == 180)
			{
				if (stageSpawnComplete == false)
				{
					if (zombieStageBossSpawn != 0)
					{
						zombieArray[zombieStageBossSpawn - 1].setInitialised(true);
						zombieArray[zombieStageBossSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							zombieArray[zombieStageBossSpawn - 1].setX(0 + zombieArray[zombieStageBossSpawn - 1].getWidth());
							zombieArray[zombieStageBossSpawn - 1].setY(0 + zombieArray[zombieStageBossSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							zombieArray[zombieStageBossSpawn - 1].setX(0 + zombieArray[zombieStageBossSpawn - 1].getWidth());
							zombieArray[zombieStageBossSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageBossSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							zombieArray[zombieStageBossSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageBossSpawn - 1].getWidth());
							zombieArray[zombieStageBossSpawn - 1].setY(GAME_HEIGHT - zombieArray[zombieStageBossSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							zombieArray[zombieStageBossSpawn - 1].setX(GAME_WIDTH - zombieArray[zombieStageBossSpawn - 1].getWidth());
							zombieArray[zombieStageBossSpawn - 1].setY(0 + zombieArray[zombieStageBossSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						zombieStageBossSpawn -= 1;
					}
					else if (TankStageBossSpawn != 0)
					{

						tankArray[TankStageBossSpawn - 1].setInitialised(true);
						tankArray[TankStageBossSpawn - 1].setStartFrame(0);
						tankArray[TankStageBossSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							tankArray[TankStageBossSpawn - 1].setX(0 + tankArray[TankStageBossSpawn - 1].getWidth());
							tankArray[TankStageBossSpawn - 1].setY(0 + tankArray[TankStageBossSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							tankArray[TankStageBossSpawn - 1].setX(0 + tankArray[TankStageBossSpawn - 1].getWidth());
							tankArray[TankStageBossSpawn - 1].setY(GAME_HEIGHT - tankArray[TankStageBossSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							tankArray[TankStageBossSpawn - 1].setX(GAME_WIDTH - tankArray[TankStageBossSpawn - 1].getWidth());
							tankArray[TankStageBossSpawn - 1].setY(GAME_HEIGHT - tankArray[TankStageBossSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							tankArray[TankStageBossSpawn - 1].setX(GAME_WIDTH - tankArray[TankStageBossSpawn - 1].getWidth());
							tankArray[TankStageBossSpawn - 1].setY(0 + tankArray[TankStageBossSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						TankStageBossSpawn -= 1;
					}
					else if (SpitterStageBossSpawn != 0)
					{

						spitterArray[SpitterStageBossSpawn - 1].setInitialised(true);
						spitterArray[SpitterStageBossSpawn - 1].setEndFrame(0);
						spawnbuffer = 0;
						if (currentSpawn == 0)
						{
							spitterArray[SpitterStageBossSpawn - 1].setX(0 + spitterArray[SpitterStageBossSpawn - 1].getWidth());
							spitterArray[SpitterStageBossSpawn - 1].setY(0 + spitterArray[SpitterStageBossSpawn - 1].getHeight());
							currentSpawn = 1;
						}
						else if (currentSpawn == 1)
						{
							spitterArray[SpitterStageBossSpawn - 1].setX(0 + spitterArray[SpitterStageBossSpawn - 1].getWidth());
							spitterArray[SpitterStageBossSpawn - 1].setY(GAME_HEIGHT - spitterArray[SpitterStageBossSpawn - 1].getHeight());
							currentSpawn = 2;
						}
						else if (currentSpawn == 2)
						{
							spitterArray[SpitterStageBossSpawn - 1].setX(GAME_WIDTH - spitterArray[SpitterStageBossSpawn - 1].getWidth());
							spitterArray[SpitterStageBossSpawn - 1].setY(GAME_HEIGHT - spitterArray[SpitterStageBossSpawn - 1].getHeight());
							currentSpawn = 3;
						}
						else if (currentSpawn == 3)
						{
							spitterArray[SpitterStageBossSpawn - 1].setX(GAME_WIDTH - spitterArray[SpitterStageBossSpawn - 1].getWidth());
							spitterArray[SpitterStageBossSpawn - 1].setY(0 + spitterArray[SpitterStageBossSpawn - 1].getHeight());
							currentSpawn = 0;
						}
						SpitterStageBossSpawn -= 1;
					}
					else
					{
						stageSpawnComplete = false;
						zombieStageBossSpawn = 20;
						TankStageBossSpawn = 8;
						SpitterStageBossSpawn = 5;
					}
				}
			}

			else
			{
				spawnbuffer += 1;
			}
			if (stageSpawnComplete == true)
			{
				stageSpawnComplete = false;
			}
			/////////////////////////////////////////////////////////////////////////////////
			//////BOSS MOTIONS RELOADING -> CHANNELING -> ATTACKING -> RELOADING -> etc//////
			/////////////////////////////////////////////////////////////////////////////////
			if (boss.getForm() == 1) //boss form 1 :: BARON
			{
				if (boss.isReloading())
				{
					for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
					{
						CannonArray[cannonNo].setInitialised(false);
					}
					boss.setFrames(bossNS::BARON_START_FRAME, bossNS::BARON_END_FRAME);
					boss.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
					boss.setLoop(true);
					if (fpscounter % 60 == 0) //for every second
					{
						BARON_RELOADING_TIMER--;
					}
					if (BARON_RELOADING_TIMER == 0) //if reload time is up
					{
						boss.changeMotion(boss.isReloading());
						boss.setCurrentFrame(bossNS::BARON_CHANNEL_START_FRAME);
						BARON_CHANNELING_TIMER = bossNS::BARON_CHANNELING_TIMER;
					}
				}
				else if (boss.isChanneling())
				{
					boss.setFrames(bossNS::BARON_CHANNEL_START_FRAME, bossNS::BARON_CHANNEL_END_FRAME);
					boss.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
					boss.setLoop(true);
					if (fpscounter % 60 == 0)
					{
						BARON_CHANNELING_TIMER--;
					}
					if (BARON_CHANNELING_TIMER == 0) //if channel time is up
					{
						boss.changeMotion(boss.isChanneling());
						boss.setCurrentFrame(bossNS::BARON_ATTACK_FRAME);
						BARON_ATTACKING_TIMER = bossNS::BARON_ATTACKING_TIMER;
						for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
						{
							CannonArray[cannonNo].setX(Cannon::X); //set bullet positions
							CannonArray[cannonNo].setY(Cannon::Y);
							shoot = true;
						}
					}
				}
				else if (boss.isAttacking())
				{
					if (shoot)
					{
						for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
						{
							CannonArray[cannonNo].setInitialised(true);
							CannonArray[cannonNo].setActive(true);
							shoot = false;
						}
					}
					for (int i = 0; i <= 8; i++)
					{
						CannonArray[i].setVelocityX(400.0f);
					}
					for (int i = 8; i <= 24; i++)
					{
						CannonArray[i].setVelocityY(400.0f);
					}
					for (int i = 24; i <= 40; i++)
					{
						CannonArray[i].setVelocityX(-400.0f);
					}
					for (int i = 40; i <= 56; i++)
					{
						CannonArray[i].setVelocityY(-400.0f);
					}
					for (int i = 56; i < 64; i++)
					{
						CannonArray[i].setVelocityX(400.0f);
					}
					float Sy = 0.0f;
					for (int i = 0; i < 8; i++)
					{
						CannonArray[i].setVelocityY(Sy);
						Sy += 50.0f;
					}
					float Sx = 400.0f;
					for (int i = 8; i < 24; i++)
					{
						CannonArray[i].setVelocityX(Sx);
						Sx -= 50.0f;
					}
					float Wy = 400.0f;
					for (int i = 24; i < 40; i++)
					{
						CannonArray[i].setVelocityY(Wy);
						Wy -= 50.0f;
					}
					float Nx = -400.0f;
					for (int i = 40; i < 56; i++)
					{
						CannonArray[i].setVelocityX(Nx);
						Nx += 50.0f;
					}
					float Ey = -400.0f;
					for (int i = 56; i < 64; i++)
					{
						CannonArray[i].setVelocityY(Ey);
						Ey += 50.0f;
					}

					for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
					{
						CannonArray[cannonNo].update(frameTime);
					}
					boss.setFrames(bossNS::BARON_ATTACK_FRAME, bossNS::BARON_ATTACK_FRAME);	//no animation
					if (fpscounter % 60 == 0)
					{
						BARON_ATTACKING_TIMER--;
					}
					if (BARON_ATTACKING_TIMER == 0) //if attack time is up
					{
						boss.changeMotion(boss.isAttacking());
						boss.setCurrentFrame(bossNS::BARON_START_FRAME);
						BARON_RELOADING_TIMER = bossNS::BARON_RELOADING_TIMER;

					}
				}
			}
			else if (boss.getForm() == 2) //boss form 2 :: NORAB
			{
				if (fpscounter % 5 == 0)
				{
					boss.setPrev(boss.getX(), boss.getY());
				}
				if (boss.isReloading())
				{
					boss.setFrames(bossNS::NORAB_START_FRAME, bossNS::NORAB_END_FRAME);
					boss.setFrameDelay(bossNS::NORAB_ANIMATION_DELAY);
					boss.setLoop(true);
					if (fpscounter % 60 == 0)
					{
						NORAB_RELOADING_TIMER--;
					}
					if (NORAB_RELOADING_TIMER == 0) //if reload time is up
					{
						boss.changeMotion(boss.isReloading());
						boss.setCurrentFrame(bossNS::NORAB_CHANNEL_START_FRAME);
						NORAB_CHANNELING_TIMER = bossNS::NORAB_CHANNELING_TIMER;
					}
				}
				else if (boss.isChanneling())
				{
					boss.setFrames(bossNS::NORAB_CHANNEL_START_FRAME, bossNS::NORAB_CHANNEL_END_FRAME);
					boss.setFrameDelay(bossNS::NORAB_ANIMATION_DELAY);
					boss.setLoop(true);
					if (fpscounter % 60 == 0)
					{
						NORAB_CHANNELING_TIMER--;
					}
					if (NORAB_CHANNELING_TIMER == 0) //if channel time is up
					{
						boss.changeMotion(boss.isChanneling());
						boss.setCurrentFrame(bossNS::NORAB_ATTACK_FRAME);
						NORAB_ATTACKING_TIMER = bossNS::NORAB_ATTACKING_TIMER;
					}
				}
				else if (boss.isAttacking())
				{
					boss.setCurrentFrame(bossNS::NORAB_ATTACK_FRAME);	//no animation			
					VECTOR2 direction;
					direction.x = player1.getX() - boss.getX();
					direction.y = player1.getY() - boss.getY();
					float hypotenuse = sqrt(direction.x * direction.x + direction.y * direction.y);
					direction.x /= hypotenuse;
					direction.y /= hypotenuse;
					direction.x *= bossNS::CHARRRGE_SPEED;
					direction.y *= bossNS::CHARRRGE_SPEED;
					boss.setVelocity(direction);
					boss.CHARRRGE(frameTime);
					boss.setFrames(bossNS::NORAB_ATTACK_FRAME, bossNS::NORAB_ATTACK_FRAME);	//no animation
					float angle = atan2(player1.getY() - boss.getY(), player1.getX() - boss.getX()) * (180 / PI) + 90;
					boss.setDegrees(angle);
					if (fpscounter % 60 == 0)
					{
						NORAB_ATTACKING_TIMER--;
					}
					if (NORAB_ATTACKING_TIMER == 0) //if attack time is up
					{
						boss.changeMotion(boss.isAttacking());
						boss.setCurrentFrame(bossNS::NORAB_START_FRAME);
						angle = 0.0f;
						boss.setDegrees(angle);
						NORAB_RELOADING_TIMER = bossNS::NORAB_RELOADING_TIMER;
					}
				}
			}
			if (boss.hasShield() == true)
			{
				shield.update(frameTime);
				shield.setX(shield.getprevX());
				shield.setY(shield.getprevY());
			}
		}

		map.update(frameTime);
		boss.update(frameTime);
		if (boss.hasDied()) // win condition
		{
			winScreen.setInitialised(true);
			state = 4;
		}
	}
	else if (state == 3)
	{
		// LOSE SCREEN
		loseScreen.update(frameTime);
		clearAllMobs();
		if (input->getMouseLButton() == true)
		{			
			startScreen.setInitialised(true);
			instructionScreen.setInitialised(true);
			loseScreen.setInitialised(false);
			player1.setHp(20);
			//revive boss
			boss.setHP(500);
			boss.setActive(false);
			boss.setSpawn(false);
			boss.setDied(false);
			boss.setDegrees(0.0f);
			for (int bossCannon = 0; bossCannon < (sizeof(CannonArray) / sizeof(*CannonArray)); bossCannon++)
			{
				if (CannonArray[bossCannon].isInitialised() == true)
				{
					CannonArray[bossCannon].setInitialised(false);
				}
			}
			state = 0;
			this->clickBuffer = 0;
			stage = 0;
			player1.setDied(false);
			loseScreen.setCurrentFrame(0);
			player1.setX(GAME_WIDTH / 2);
			player1.setY(GAME_HEIGHT / 2);
			zombieStageOneSpawn = 50;
			zombieStageTwoSpawn = 45;
			TankStageTwoSpawn = 5;
			zombieStageThreeSpawn = 35;
			TankStageThreeSpawn = 5;
			SpitterStageThreeSpawn = 10;
		}
	}
	else if (state == 4)
	{
		// WIN SCREEN
		winScreen.update(frameTime);
		clearAllMobs();
		if (input->getMouseLButton() == true)
		{
			startScreen.setInitialised(true);
			instructionScreen.setInitialised(true);
			winScreen.setInitialised(false);
			player1.setHp(20);
			//revive boss
			boss.setHP(500);
			boss.setActive(false);
			boss.setSpawn(false);
			boss.setDied(false);
			boss.setDegrees(0.0f);
			for (int bossCannon = 0; bossCannon < (sizeof(CannonArray) / sizeof(*CannonArray)); bossCannon++)
			{
				if (CannonArray[bossCannon].isInitialised() == true)
				{
					CannonArray[bossCannon].setInitialised(false);
				}
			}
			state = 0;
			this->clickBuffer = 0;
			stage = 0;
			player1.setDied(false);
			loseScreen.setCurrentFrame(0);
			player1.setX(GAME_WIDTH / 2);
			player1.setY(GAME_HEIGHT / 2);
			zombieStageOneSpawn = 50;
			zombieStageTwoSpawn = 45;
			TankStageTwoSpawn = 5;
			zombieStageThreeSpawn = 35;
			TankStageThreeSpawn = 5;
			SpitterStageThreeSpawn = 10;
		}
	}
}

//=============================================================================
// render game items
//=============================================================================
void dontdie::render()
{
	const int BUF_SIZE = 20;
	static char buffer[BUF_SIZE];

	graphics->spriteBegin();
	//////////////////////////////////boss HP bar////////////////////////////////////
	float bossHP = boss.getHP()/bossNS::MAXHP;  //500 pixel = 1HP
	if (!bossCURHPTexture.initialize(graphics, BOSS_CUR_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss CURRENT HP texture"));
	if (!bossCURHP.initialize(graphics, bossHP*500, 32, 1, &bossCURHPTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss CURRENT HP BAR"));
	bossCURHP.setX(110); //centerize the HP bar
	bossCURHP.setY(GAME_HEIGHT - 32); //show the HP bar at the bottom
	/////////////////////////////////////////////////////////////////////////////////
	for (int row = 0; row < MAP_HEIGHT; row++)       // for each row of map
	{
		map.setY((float)(row*TEXTURE_SIZE)); // set tile Y
		for (int col = 0; col < MAP_WIDTH; col++)    // for each column of map
		{
			if (tileMap[row][col] >= 0)          // if tile present
			{
				map.setCurrentFrame(tileMap[row][col]);    // set tile texture
				map.setX((float)(col*TEXTURE_SIZE) + mapX);   // set tile X
															  // if tile on screen
				if (map.getX() > -TEXTURE_SIZE && map.getX() < GAME_WIDTH)
				{
					map.draw();                // draw tile
				}
			}
		}
	}
	//Put it on top
	if (boss.isSpawn()) //if boss spawn
	{
		bossMAXHP.draw(); //draw MAXHP bar
		if (boss.getHP() > 0)
		{
			bossCURHP.draw(); //draw boss current HP bar
		}
	}

	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			zombieArray[zomb].draw();
		}
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			tankArray[tank].draw();
		}
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (spitterArray[spitter].isInitialised() == true)
		{
			spitterArray[spitter].draw();
		}
	}
	for (int spitterb = 0; spitterb < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterb++)
	{
		if (spitterbulletArray[spitterb].isInitialised() == true)
		{
			spitterbulletArray[spitterb].draw();
		}
	}
	for (int i = 0; i < 10; i++)
	{
		wallArray[i].draw();
	}

	player1.draw();     //adds the player into the scene
	playerhealth.draw();

	for (int bullet = 0; bullet < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); bullet++)
	{
		if (pistolBulletArray[bullet].isInitialized() == true)
		{
			pistolBulletArray[bullet].draw();
		}
	}

	for (int bullet = 0; bullet < (sizeof(rifleBulletArray) / sizeof(*rifleBulletArray)); bullet++)
	{
		if (rifleBulletArray[bullet].isInitialized() == true)
		{
			rifleBulletArray[bullet].draw();
		}
	}


	for (int bullet = 0; bullet < (sizeof(smgBulletArray) / sizeof(*smgBulletArray)); bullet++)
	{
		if (smgBulletArray[bullet].isInitialized() == true)
		{
			smgBulletArray[bullet].draw();
		}
	}

	for (int bullet = 0; bullet < (sizeof(shotgunBulletArray) / sizeof(*shotgunBulletArray)); bullet++)
	{
		if (shotgunBulletArray[bullet].isInitialized() == true)
		{
			shotgunBulletArray[bullet].draw();
		}
	}
	if (boss.getActive()) //if boss spawn
	{
		boss.draw(); //draw my boss
		if (boss.hasShield()) //draw my shield
			shield.draw();
		if (boss.isAttacking() && boss.getForm() == 1)
		{
			for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
			{
				if (CannonArray[cannonNo].isInitialised() == true)
				{
					CannonArray[cannonNo].draw();
				}

			}
		}
	}

	dxFontSmall->setFontColor(graphicsNS::BLACK);
	dxFontMedium->setFontColor(graphicsNS::BLACK);
	dxFontLarge->setFontColor(graphicsNS::BLACK);
	dxFont.setFontColor(graphicsNS::BLACK);
	if (fpsOn)
	{
		_snprintf_s(buffer, BUF_SIZE, "%d ", (int)player1.getHp());
		dxFont.print(buffer, 39, 0);
	}
	
	if (instructionScreen.isInitialised() == true)
	{
		instructionScreen.draw();
	}

	if (startScreen.isInitialised() == true)
	{
		startScreen.draw();
	}
	if (loseScreen.isInitialised() == true)
	{
		loseScreen.draw();
	}
	if (winScreen.isInitialised() == true)
	{
		winScreen.draw();
	}


	graphics->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void dontdie::releaseAll()
{
	zombieTexture.onLostDevice();
	mapTexture.onLostDevice();
	wallTexture.onLostDevice();
	playerTexture.onLostDevice();
	bossTexture.onLostDevice();
	bossMAXHPTexture.onLostDevice();
	bossCURHPTexture.onLostDevice();
	tankTexture.onLostDevice();
	spitterTexture.onLostDevice();
	spitterbulletTexture.onLostDevice();
	Game::releaseAll();
	PbulletTexture.onLostDevice();
	//SMGbulletTexture.onLostDevice();
	//ShotgunbulletTexture.onLostDevice();
	//RiflebulletTexture.onLostDevice();
	InstructionTexture.onLostDevice();
	StartTexture.onLostDevice();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void dontdie::resetAll()
{
	zombieTexture.onResetDevice();
	mapTexture.onResetDevice();
	wallTexture.onResetDevice();
	playerTexture.onResetDevice();
	bossTexture.onResetDevice();
	bossMAXHPTexture.onResetDevice();
	bossCURHPTexture.onResetDevice();
	tankTexture.onResetDevice();
	spitterTexture.onResetDevice();
	spitterbulletTexture.onResetDevice();
	PbulletTexture.onResetDevice();
	//SMGbulletTexture.onResetDevice();
	//ShotgunbulletTexture.onResetDevice();
	//RiflebulletTexture.onResetDevice();
	InstructionTexture.onResetDevice();
	StartTexture.onResetDevice();
	Game::resetAll();
	return;
}


void dontdie::collisions()
{
	VECTOR2 tempVector;
	for (int bullet = 0; bullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); bullet++)
	{
		if (spitterbulletArray[bullet].isInitialised() == true)
		{
			if (spitterbulletArray[bullet].collidesWith(player1, tempVector))
			{
				spitterbulletArray[bullet].setInitialised(false);
				player1.damageMe(2);
				
			}

		}

	}

	for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
	{
		if (pistolBulletArray[pistolb].isInitialized() == true)
		{
				for (int zombie = 0; zombie < (sizeof(zombieArray) / sizeof(*zombieArray)); zombie++)
				{
					if (zombieArray[zombie].isInitialised() == true)
					{
						if (pistolBulletArray[pistolb].collidesWith(zombieArray[zombie], tempVector))
						{
							audio->stopCue(MOB_DAMAGE);
							audio->playCue(MOB_DAMAGE);
							zombieArray[zombie].damageZombie(pistolBulletArray[pistolb].getpistolDamage());
							pistolBulletArray[pistolb].setInitialized(false);
							if (zombieArray[zombie].getHealth() <= 0)
							{
								zombieArray[zombie].setInitialised(false);
							}
						}
					}
				}

			for (int i = 0; i < 10; i++)
			{
				if (pistolBulletArray[pistolb].collidesWith(wallArray[i], tempVector) || pistolBulletArray[pistolb].getX() < 0 || pistolBulletArray[pistolb].getY() < 0 || pistolBulletArray[pistolb].getX() > GAME_WIDTH || pistolBulletArray[pistolb].getY() > GAME_HEIGHT)
				{
					if (pistolBulletArray[pistolb].isInitialized() == true)
					{
						pistolBulletArray[pistolb].setInitialized(false);
					}
					
				}
			}
		}
	}
	if (player1.collidesWith(boss, tempVector))
	{
		if (boss.getForm() == 2)
		{
			player1.damageMe(3);
			
			player1.revertLocation();
			boss.revertLocation();
			NORAB_ATTACKING_TIMER = 0;
		}
		else
		{
			player1.damageMe(boss.getDamage());
			
		}	
		boss.setPrev(boss.getX(), boss.getY());
	}
	for (int cannon = 0; cannon < (sizeof(CannonArray) / sizeof(*CannonArray)); cannon++)
	{
		if (CannonArray[cannon].isInitialised() == true)
		{
			if (CannonArray[cannon].collidesWith(player1, tempVector))
			{
				CannonArray[cannon].setInitialised(false);
				CannonArray[cannon].setActive(false);
				player1.damageMe(CannonArray[cannon].getdamage());
				
			}
			for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
			{
				if (CannonArray[cannon].collidesWith(wallArray[i], tempVector))
				{
					CannonArray[cannon].setInitialised(false);
					CannonArray[cannon].setActive(false);
				}
			}
		}

	}

	for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
	{
		if (player1.collidesWith(wallArray[i], tempVector))
		{
			player1.revertLocation();
		}
		for (int bullet = 0; bullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); bullet++)
		{
			if (spitterbulletArray[bullet].isInitialised() == true)
			{
				if (spitterbulletArray[bullet].collidesWith(wallArray[i], tempVector))
				{
					spitterbulletArray[bullet].setInitialised(false);
				}
				if (spitterbulletArray[bullet].getX() < 0 || spitterbulletArray[bullet].getX() > GAME_WIDTH || spitterbulletArray[bullet].getY() < 0 || spitterbulletArray[bullet].getY() > GAME_HEIGHT)
				{
					spitterbulletArray[bullet].setInitialised(false);
				}

			}
		}
	}



	//when palyerbullet touches the zombie
	//for loop to track which bullet
	for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
	{
		if (pistolBulletArray[pistolb].isInitialized() == true)
		{
			if (boss.isSpawn() == true)
			{
				if (pistolBulletArray[pistolb].collidesWith(boss, tempVector))
				{
					boss.takesDamage(10);
					pistolBulletArray[pistolb].setInitialized(false);
				}
				if (pistolBulletArray[pistolb].collidesWith(shield, tempVector))
				{
					pistolBulletArray[pistolb].setInitialized(false);
				}
			}

			for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
			{
				if (tankArray[tank].isInitialised() == true)
				{
					if (pistolBulletArray[pistolb].collidesWith(tankArray[tank] ,tempVector))
					{
						audio->stopCue(MOB_DAMAGE);
						audio->playCue(MOB_DAMAGE);
						if (tankArray[tank].getHealth() <= 0)
						{
							tankArray[tank].setInitialised(false);
						}
						else
						{
							tankArray[tank].setHealth(tankArray[tank].getHealth() - 2);
						}
						pistolBulletArray[pistolb].setInitialized(false);
					}
				}

			}
			for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
			{
				if (spitterArray[spitter].isInitialised() == true)
				{
					if (pistolBulletArray[pistolb].collidesWith(spitterArray[spitter], tempVector))
					{
						audio->stopCue(MOB_DAMAGE);
						audio->playCue(MOB_DAMAGE);
						if (spitterArray[spitter].getHealth() <= 0)
						{
							spitterArray[spitter].setInitialised(false);
						}
						else
						{
							spitterArray[spitter].setHealth(spitterArray[spitter].getHealth() - 2);
						}
						pistolBulletArray[pistolb].setInitialized(false);
					}
				}
			}
		}
	}
	



}

void dontdie::ai()
{
	//zombie AI
	VECTOR2 dir, tempVec, wallVec;
	float up, down, left, right, upChange, downChange, leftChange, rightChange;
	string failDirection = "";
	int voronoi;
	bool failCheck = false;
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			dir.x = player1.getX() - zombieArray[zomb].getX();
			dir.y = player1.getY() - zombieArray[zomb].getY();
			float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
			dir.x /= hyp;
			dir.y /= hyp;
			dir.x *= zombieNS::ZOMBIE_SPEED;
			dir.y *= zombieNS::ZOMBIE_SPEED;
			zombieArray[zomb].setVelocity(dir);
			float angle = atan2(player1.getY() - zombieArray[zomb].getY(), player1.getX() - zombieArray[zomb].getX()) * (180 / PI) + 90;
			zombieArray[zomb].setDegrees(angle);
			for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
			{
				if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 0 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() - 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					zombieArray[zomb].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 1 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() + 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					zombieArray[zomb].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 2 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() + 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					zombieArray[zomb].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 3 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() - 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					zombieArray[zomb].setVelocity(dir);
				}
				else
				{
					if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
					{
						zombieArray[zomb].revertLocation();
						zombieArray[zomb].setX(zombieArray[zomb].getX() + 1);
						if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "right";
							// zombieArray[zombie].revertLocation();
						}
						zombieArray[zomb].revertLocation();
						if (failDirection == "")
						{
							zombieArray[zomb].setX(zombieArray[zomb].getX() - 1);
							if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "left";
								// zombieArray[zombie].revertLocation();
							}
							zombieArray[zomb].revertLocation();
						}
						if (failDirection == "")
						{
							zombieArray[zomb].setY(zombieArray[zomb].getY() - 1);
							if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "up";
								// zombieArray[zombie].revertLocation();
							}
							zombieArray[zomb].revertLocation();
						}
						if (failDirection == "")
						{
							zombieArray[zomb].setY(zombieArray[zomb].getY() + 1);
							if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "down";
								// zombieArray[zombie].revertLocation();
							}
							zombieArray[zomb].revertLocation();
						}
						if (failDirection == "right")
						{

							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= zombieArray[zomb].getY())
							{
								upChange = 1;
								downChange = -1;
							}
							else
							{
								upChange = -1;
								downChange = 1;

							}
							up = sqrt(xValue * xValue + (yValue + upChange) * (yValue + upChange));
							down = sqrt(xValue * xValue + (yValue + downChange) * (yValue + downChange));
							//left = sqrt((xValue-1) * (xValue-1) + (yValue) * (yValue));
							if (up < down)
							{
								wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (down == up)
							{
								wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							//else if (left <= up && left <= down)
							//{
							//	wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
							//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
						}
						else if (failDirection == "left")
						{
							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= zombieArray[zomb].getY())
							{
								upChange = 1;
								downChange = -1;
							}
							else
							{
								upChange = -1;
								downChange = 1;

							}


							up = sqrt(xValue * xValue + (yValue + upChange)* (yValue + upChange));
							down = sqrt(xValue * xValue + (yValue + downChange)* (yValue + downChange));
							//right = sqrt((xValue + 1) * (xValue + 1) + (yValue) * (yValue));
							if (up < down)
							{
								wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (down == up)
							{
								wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							//else if (right <= up && right <= down)
							//{
							//	wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
							//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
						}
						else if (failDirection == "up")
						{
							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= zombieArray[zomb].getX())
							{
								leftChange = 1;
								rightChange = -1;
							}
							else
							{
								leftChange = -1;
								rightChange = 1;
							}
							left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
							//down = sqrt(xValue * xValue + (yValue + 1)* (yValue + 1));
							right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
							if (left < right)
							{
								wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (right < left)
							{
								wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (right == left)
							{
								wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
						}
						else if (failDirection == "down")
						{
							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= zombieArray[zomb].getX())
							{
								leftChange = 1;
								rightChange = -1;
							}
							else
							{
								leftChange = -1;
								rightChange = 1;
							}
							left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
							//up = sqrt(xValue * xValue + (yValue - 1)* (yValue - 1));
							right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
							if (left < right)
							{
								wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}
							//else if (up <= left && up <= right)
							//{
							//	wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;;
							//	wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
							else if (right < left)
							{
								wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;;
								zombieArray[zomb].setVelocity(wallVec);
							}
							else if (right == left)
							{
								wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								zombieArray[zomb].setVelocity(wallVec);
							}

						}

					}
				}

			}
			VECTOR2 tempVector;
			if (player1.collidesWith(zombieArray[zomb], tempVector))
			{
				player1.revertLocation();
				zombieArray[zomb].revertLocation();
				player1.damageMe(zombieArray[zomb].getDamage());
				
			}
			zombieArray[zomb].setPrev(zombieArray[zomb].getX(), zombieArray[zomb].getY());
		}
	}



	//Tank AI
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			dir.x = player1.getX() - tankArray[tank].getX();
			dir.y = player1.getY() - tankArray[tank].getY();
			float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
			dir.x /= hyp;
			dir.y /= hyp;
			dir.x *= zombieNS::ZOMBIE_SPEED;
			dir.y *= zombieNS::ZOMBIE_SPEED;
			tankArray[tank].setVelocity(dir);
			float angle = atan2(player1.getY() - tankArray[tank].getY(), player1.getX() - tankArray[tank].getX()) * (180 / PI) + 90;
			tankArray[tank].setDegrees(angle);
			for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
			{
				if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 0 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() - 1);
					tankArray[tank].setY(tankArray[tank].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					tankArray[tank].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 1 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() + 1);
					tankArray[tank].setY(tankArray[tank].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					tankArray[tank].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 2 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() + 1);
					tankArray[tank].setY(tankArray[tank].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					tankArray[tank].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 3 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() - 1);
					tankArray[tank].setY(tankArray[tank].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					tankArray[tank].setVelocity(dir);
				}
				else
				{
					if (tankArray[tank].collidesWith(wallArray[i], tempVec))
					{
						tankArray[tank].revertLocation();
						tankArray[tank].setX(tankArray[tank].getX() + 1);
						if (tankArray[tank].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "right";
							// zombieArray[zombie].revertLocation();
						}
						tankArray[tank].revertLocation();
						if (failDirection == "")
						{
							tankArray[tank].setX(tankArray[tank].getX() - 1);
							if (tankArray[tank].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "left";
								// zombieArray[zombie].revertLocation();
							}
							tankArray[tank].revertLocation();
						}
						if (failDirection == "")
						{
							tankArray[tank].setY(tankArray[tank].getY() - 1);
							if (tankArray[tank].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "up";
								// zombieArray[zombie].revertLocation();
							}
							tankArray[tank].revertLocation();
						}
						if (failDirection == "")
						{
							tankArray[tank].setY(tankArray[tank].getY() + 1);
							if (tankArray[tank].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "down";
								// zombieArray[zombie].revertLocation();
							}
							tankArray[tank].revertLocation();
						}
						if (failDirection == "right")
						{

							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= tankArray[tank].getY())
							{
								upChange = 1;
								downChange = -1;
							}
							else
							{
								upChange = -1;
								downChange = 1;

							}
							up = sqrt(xValue * xValue + (yValue + upChange) * (yValue + upChange));
							down = sqrt(xValue * xValue + (yValue + downChange) * (yValue + downChange));
							//left = sqrt((xValue-1) * (xValue-1) + (yValue) * (yValue));
							if (up < down)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = -1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = 1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down == up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = -1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							//else if (left <= up && left <= down)
							//{
							//	wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
							//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
						}
						else if (failDirection == "left")
						{
							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= tankArray[tank].getY())
							{
								upChange = 1;
								downChange = -1;
							}
							else
							{
								upChange = -1;
								downChange = 1;

							}


							up = sqrt(xValue * xValue + (yValue + upChange)* (yValue + upChange));
							down = sqrt(xValue * xValue + (yValue + downChange)* (yValue + downChange));
							//right = sqrt((xValue + 1) * (xValue + 1) + (yValue) * (yValue));
							if (up < down)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = -1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = 1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down == up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = 1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							//else if (right <= up && right <= down)
							//{
							//	wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
							//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
						}
						else if (failDirection == "up")
						{
							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= tankArray[tank].getX())
							{
								leftChange = 1;
								rightChange = -1;
							}
							else
							{
								leftChange = -1;
								rightChange = 1;
							}
							left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
							//down = sqrt(xValue * xValue + (yValue + 1)* (yValue + 1));
							right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
							if (left < right)
							{
								wallVec.x = -1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (right < left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (right == left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
						}
						else if (failDirection == "down")
						{
							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= tankArray[tank].getX())
							{
								leftChange = 1;
								rightChange = -1;
							}
							else
							{
								leftChange = -1;
								rightChange = 1;
							}
							left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
							//up = sqrt(xValue * xValue + (yValue - 1)* (yValue - 1));
							right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
							if (left < right)
							{
								wallVec.x = -1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							//else if (up <= left && up <= right)
							//{
							//	wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;;
							//	wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
							else if (right < left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (right == left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}

						}

					}
				}

			}
			VECTOR2 tempVector;
			if (player1.collidesWith(tankArray[tank], tempVector))
			{
				player1.revertLocation();
				tankArray[tank].revertLocation();
				player1.damageMe(tankArray[tank].getDamage());
				
			}
			tankArray[tank].setPrev(tankArray[tank].getX(), tankArray[tank].getY());
		}
	}

	//Spitter AI
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (spitterArray[spitter].isInitialised() == true)
		{
			float xValue = player1.getX() - spitterArray[spitter].getX();
			if (xValue < 0)
			{
				xValue *= -1;
			}
			float yValue = player1.getY() - spitterArray[spitter].getY();
			if (yValue < 0)
			{
				yValue *= -1;
			}
			float distanceToPlayer = sqrt((xValue) * (xValue)+(yValue) * (yValue));
			if (distanceToPlayer > 200)
			{
				spitterArray[spitter].setEndFrame(0);
				dir.x = player1.getX() - spitterArray[spitter].getX();
				dir.y = player1.getY() - spitterArray[spitter].getY();
				float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
				dir.x /= hyp;
				dir.y /= hyp;
				dir.x *= zombieNS::ZOMBIE_SPEED;
				dir.y *= zombieNS::ZOMBIE_SPEED;
				spitterArray[spitter].setVelocity(dir);
				float angle = atan2(player1.getY() - spitterArray[spitter].getY(), player1.getX() - spitterArray[spitter].getX()) * (180 / PI) + 90;
				spitterArray[spitter].setDegrees(angle);
				for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
				{
					if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 0 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() - 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() - 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * -1;
						//dir.y = zombieNS::ZOMBIE_SPEED * -1;
						spitterArray[spitter].setVelocity(dir);
					}
					else if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 1 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() + 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() - 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * 1;
						//dir.y = zombieNS::ZOMBIE_SPEED * -1;
						spitterArray[spitter].setVelocity(dir);
					}
					else if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 2 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() + 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() + 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * 1;
						//dir.y = zombieNS::ZOMBIE_SPEED * 1;
						spitterArray[spitter].setVelocity(dir);
					}
					else if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 3 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() - 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() + 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * -1;
						//dir.y = zombieNS::ZOMBIE_SPEED * 1;
						spitterArray[spitter].setVelocity(dir);
					}
					else
					{
						if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
						{
							spitterArray[spitter].revertLocation();
							spitterArray[spitter].setX(spitterArray[spitter].getX() + 1);
							if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "right";
								// zombieArray[zombie].revertLocation();
							}
							spitterArray[spitter].revertLocation();
							if (failDirection == "")
							{
								spitterArray[spitter].setX(spitterArray[spitter].getX() - 1);
								if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
								{
									failDirection = "left";
									// zombieArray[zombie].revertLocation();
								}
								spitterArray[spitter].revertLocation();
							}
							if (failDirection == "")
							{
								spitterArray[spitter].setY(spitterArray[spitter].getY() - 1);
								if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
								{
									failDirection = "up";
									// zombieArray[zombie].revertLocation();
								}
								spitterArray[spitter].revertLocation();
							}
							if (failDirection == "")
							{
								spitterArray[spitter].setY(spitterArray[spitter].getY() + 1);
								if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
								{
									failDirection = "down";
									// zombieArray[zombie].revertLocation();
								}
								spitterArray[spitter].revertLocation();
							}
							if (failDirection == "right")
							{

								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getY() >= spitterArray[spitter].getY())
								{
									upChange = 1;
									downChange = -1;
								}
								else
								{
									upChange = -1;
									downChange = 1;

								}
								up = sqrt(xValue * xValue + (yValue + upChange) * (yValue + upChange));
								down = sqrt(xValue * xValue + (yValue + downChange) * (yValue + downChange));
								//left = sqrt((xValue-1) * (xValue-1) + (yValue) * (yValue));
								if (up < down)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = -1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down < up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = 1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down == up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = -1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								//else if (left <= up && left <= down)
								//{
								//	wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
								//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								//	 zombieArray[zombie].setVelocity(wallVec);
								//}
							}
							else if (failDirection == "left")
							{
								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getY() >= spitterArray[spitter].getY())
								{
									upChange = 1;
									downChange = -1;
								}
								else
								{
									upChange = -1;
									downChange = 1;

								}


								up = sqrt(xValue * xValue + (yValue + upChange)* (yValue + upChange));
								down = sqrt(xValue * xValue + (yValue + downChange)* (yValue + downChange));
								//right = sqrt((xValue + 1) * (xValue + 1) + (yValue) * (yValue));
								if (up < down)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = -1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down < up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = 1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down == up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = 1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								//else if (right <= up && right <= down)
								//{
								//	wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
								//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
								//	 zombieArray[zombie].setVelocity(wallVec);
								//}
							}
							else if (failDirection == "up")
							{
								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getX() >= spitterArray[spitter].getX())
								{
									leftChange = 1;
									rightChange = -1;
								}
								else
								{
									leftChange = -1;
									rightChange = 1;
								}
								left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
								//down = sqrt(xValue * xValue + (yValue + 1)* (yValue + 1));
								right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
								if (left < right)
								{
									wallVec.x = -1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (right < left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (right == left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
							}
							else if (failDirection == "down")
							{
								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getX() >= spitterArray[spitter].getX())
								{
									leftChange = 1;
									rightChange = -1;
								}
								else
								{
									leftChange = -1;
									rightChange = 1;
								}
								left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
								//up = sqrt(xValue * xValue + (yValue - 1)* (yValue - 1));
								right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
								if (left < right)
								{
									wallVec.x = -1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								//else if (up <= left && up <= right)
								//{
								//	wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;;
								//	wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;;
								//	 zombieArray[zombie].setVelocity(wallVec);
								//}
								else if (right < left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (right == left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}

							}

						}
					}

				}
			}
			else
			{
				float angle = atan2(player1.getY() - spitterArray[spitter].getY(), player1.getX() - spitterArray[spitter].getX()) * (180 / PI) + 90;
				spitterArray[spitter].setDegrees(angle);
				dir.x = 0;
				dir.y = 0;
				spitterArray[spitter].setVelocity(dir);
				if (spitterArray[spitter].getAttackBuffer() == 20.0f)
				{
					spitterArray[spitter].setAttackBuffer(0);
					for (int bullet = 0; bullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); bullet++)
					{
						if (spitterbulletArray[bullet].isInitialised() == false)
						{
							spitterbulletArray[bullet].setInitialised(true);
							dir.x = player1.getX() - spitterArray[spitter].getX();
							dir.y = player1.getY() - spitterArray[spitter].getY();
							float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
							dir.x /= hyp;
							dir.y /= hyp;
							dir.x *= spitterbulletNS::SPITTERBULLET_SPEED;
							dir.y *= spitterbulletNS::SPITTERBULLET_SPEED;
							spitterbulletArray[bullet].setX(spitterArray[spitter].getX());
							spitterbulletArray[bullet].setY(spitterArray[spitter].getY());
							spitterbulletArray[bullet].setVelocity(dir);
							break;
						}
					}
				}
			}

			VECTOR2 tempVector;
			if (player1.collidesWith(spitterArray[spitter], tempVector))
			{
				player1.revertLocation();
			}
			spitterArray[spitter].setPrev(spitterArray[spitter].getX(), spitterArray[spitter].getY());
		}
	}

}


bool dontdie::checkStageClear()
{
	int zombieCount = 0;
	int tankCount = 0;
	int spitterCount = 0;
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			zombieCount += 1;
		}
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			tankCount += 1;
		}
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (spitterArray[spitter].isInitialised() == true)
		{
			zombieCount += 1;
		}
	}
	if (zombieCount == 0 && tankCount == 0 && spitterCount == 0 && boss.isSpawn() == false)
	{
		for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
		{
			zombieArray[zomb].setHealth(1);
		}
		for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
		{
			tankArray[tank].setHealth(5);
		}
		for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
		{
			spitterArray[spitter].setHealth(2);
		}
		return true;
	}
	else
	{
		return false;
	}
}

void dontdie::clearAllMobs()
{
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		zombieArray[zomb].setInitialised(false);
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		tankArray[tank].setInitialised(false);
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		spitterArray[spitter].setInitialised(false);
	}
	for (int spitterbullet = 0; spitterbullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterbullet++)
	{
		if (spitterbulletArray[spitterbullet].isInitialised() == true)
		{
			spitterbulletArray[spitterbullet].setInitialised(false);
		}
	}
}
