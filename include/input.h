#ifndef INPUT_H
#define INPUT_H

#include <object2D.h>

class Input;

struct KeyState
{
	SDL_Scancode code;
	bool moveset = 1; // If these are gameplay key or not
	bool key = 0;
	bool hold = 0;
	bool press();
	int threshold = 0,
		threspeak = 0;
	int keydelay = 0;

	long1D script;
	long1D script_history;

	void update(const Uint8* state, Input *input);
	bool threspass(int max);

	string0D scriptHistoryToStr();
};

struct MouseState
{
	bool click = 0;
	bool hold = 0;
	int threshold = 0,
		threspeak = 0;
	int keydelay = 0;
};

struct KeyTemplate0
{
	KeyState
		moveU = {SDL_SCANCODE_W},
		moveD = {SDL_SCANCODE_S},
		moveL = {SDL_SCANCODE_A},
		moveR = {SDL_SCANCODE_D},
		proj = {SDL_SCANCODE_R},
		equip = {SDL_SCANCODE_E},
		attack = {SDL_SCANCODE_F},
		jump = {SDL_SCANCODE_W}, // FOR TESTING
		dash = {SDL_SCANCODE_H}; 
};

struct KeyTemplate1
{
	KeyState
		moveU = {SDL_SCANCODE_UP},
		moveD = {SDL_SCANCODE_DOWN},
		moveL = {SDL_SCANCODE_LEFT},
		moveR = {SDL_SCANCODE_RIGHT},
		proj = {SDL_SCANCODE_O},
		equip = {SDL_SCANCODE_L},
		attack = {SDL_SCANCODE_P},
		jump = {SDL_SCANCODE_UP}, // FOR TESTING
		dash = {SDL_SCANCODE_RIGHTBRACKET};
};

class Player;
class Input 
{
public:
	int mouse_x, mouse_y;
	// -1: Scroll Down, 1: Scroll Up
	short wheel = 0;

// ====================================================================

	KeyState
		// Gameplay
		moveU, moveD, moveL, moveR,
		proj, equip, attack,
		jump, dash,

		// Other
		lctrl = {SDL_SCANCODE_LCTRL, 0},
		arrowU = {SDL_SCANCODE_UP, 0},
		arrowD = {SDL_SCANCODE_DOWN, 0},
		arrowL = {SDL_SCANCODE_LEFT, 0},
		arrowR = {SDL_SCANCODE_RIGHT, 0},

		slash = {SDL_SCANCODE_SLASH, 0},
		backslash = {SDL_SCANCODE_BACKSLASH, 0},

		// Function Key
		f1 = {SDL_SCANCODE_F1, 0},
		f2 = {SDL_SCANCODE_F2, 0},
		f3 = {SDL_SCANCODE_F3, 0},
		f4 = {SDL_SCANCODE_F4, 0},
		f5 = {SDL_SCANCODE_F5, 0};

	string0D script_history_full = "";

	int delay = 0;
	bool script_active = 0;

	Input();
	void setTemplate(int keytemplate);
	void update();
	void executeScript(string0D script_dir, bool from_cur = 0);

	// ==================== OBSOLETE ======================

	bool input();

	// Input
	bool1D key, click = {0, 0};
	bool1D hold, clickhold = {0, 0};

	int1D threshold;
	int1D clickthreshold = {0, 0};

	int1D threspeak;
	int1D clickthrespeak = {0, 0};

	SDL_GameController *controller;

	int key_delay = 0;
	int click_delay = 0;
	SDL_Event event;

	// Keyboard/Controller
	void setKeyDelay(int delay);
	void sethold(int i, bool held);
	bool gethold(int i);
	bool getKeyPress(int i);
	bool getthreshold(int i, int max);
	int getKeyThresValue(int i);
	int getthrespeak(int i);
	void resetthrespeak(int i);

	// Mouse Click/Motion
	void setClickDelay(int delay);
	void setClickHold(int i, bool held);
	bool getClickHold(int i);
	bool getClickPress(int i);
	bool getClickThreshold(int i, int max);
	int getClickThresValue(int i);
	int getClickThresPeak(int i);
	void resetClickThresPeak(int i);

	int getMouseX(bool fromright = 0);
	int getMouseY(bool fromtop = 0);
	int getMOffMidX();
	int getMOffMidY();
	int getMOffPlayerX(Player *player);
	int getMOffPlayerY(Player *player);
	int getMMapX(Player *player, short grid = 64);
	int getMMapY(Player *player, short grid = 64);
	bool mouseInBox(ObjectBox mbox);

	// Mouse Wheel
	void resetWheel();
	short getWheel();
};

#endif