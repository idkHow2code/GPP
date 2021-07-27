// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Three Cs DX constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))


//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "dontdie";
const char GAME_TITLE[] = "Don't Die";
const bool FULLSCREEN = false;          // windowed or fullscreen
const UINT GAME_WIDTH = 720;			// width of game in pixels
const UINT GAME_HEIGHT = 560;			// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const UINT  TILE_MAP_WIDTH = 100;           // width of tile map in tiles
const UINT  TILE_MAP_HEIGHT = 20;           // height of tile map in tiles


//graphics images
const char BOSS_IMAGE[] = "pictures\\Boss form.png";
const char BOSSCANNON_IMAGE[] = "pictures\\Boss Cannon Ball.png";
const char BOSS_SHIELD[] = "pictures\\Boss Shield.png";
const char BOSS_HP[] = "pictures\\Health pixel.png";
const char BOSS_MAX_HP[] = "pictures\\MAXHP pixel.png";
const char BOSS_CUR_HP[] = "pictures\\CURHP pixel.png";
const char START_IMAGE[] = "pictures\\start.png";
const char WIN_IMAGE[] = "pictures\\win.png";
const char LOSE_IMAGE[] = "pictures\\lose.png";
// graphic images
const char PLAYER_IMAGE[] = "pictures\\player.png"; // picture of Player
const char HEALTH_IMAGE[] = "pictures\\heart.png"; //picture of Heart
const char BULLET_IMAGE[] = "pictures\\bullets.png"; //picture of Pistol Bullet
//const char SMGBULLET_IMAGE[] = "picture\\smgbullet.png"; //picture of SMG bullet
//const char SHOTGUNBULLET_IMAGE[] = "picture\\shotgunbullet.png"; //picture of Shotgun Bullet
//const char RIFLEBULLET_IMAGE[] = "picture\\riflebullet.png"; //picture of Rifle Bullet

// zombie images
const char ZOMBIE_IMAGE[] = "pictures\\zombie.png";  // game textures

//environment images
const char MAP_IMAGE[] = "pictures\\moreTiles.png";  // Picture of background
const char WALL_IMAGE[] = "pictures\\barrier.png"; //picture of a wall
const char TANK_IMAGE[] = "pictures\\tank.png";
const char SPITTER_IMAGE[] = "pictures\\spitter.png";
const char SPITTERBULLET_IMAGE[] = "pictures\\spitterbullet.png";
const char INSTRUCTION_IMAGE[] = "pictures\\instructions.png";


// player movement
const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float PLAYER_SPEED = 100.0f;                // pixels per second
const float PLAYER_SCALE = 1.5f;                  // starting player scale


// audio files
const char WAVE_BANK[] = "audio\\Win\\waveBank.xwb";
const char SOUND_BANK[] = "audio\\Win\\soundBank.xsb";

// audio cues
const char BM_MUSIC[] = "music";
const char GUN_SHOT[] = "gunshot";
const char MOB_DAMAGE[] = "getHit";
const char PLAYER_DAMAGE[] = "scream";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = VK_OEM_3;    // `~ key for U.S.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR PLAYER_RIGHT_KEY = 0x44; //Right arrow key
const UCHAR PLAYER_LEFT_KEY = 0x41; //Left Arrow key
const UCHAR PLAYER_UP_KEY = 0x57; //Up Arrow key
const UCHAR PLAYER_DOWN_KEY = 0x53; //Down Arrow key
const UCHAR KILL_ALL = 0xC0;
const UCHAR BOSS_STAGE1 = VK_BACK; //skip to boss stage 1 cheat
const UCHAR BOSS_STAGE2 = VK_INSERT; //skip to boss stage 2 cheat
const UCHAR BOSS_CLEAR = VK_DELETE; //skip to win cheat
const UCHAR MINUS_HP = VK_DOWN;
#endif

