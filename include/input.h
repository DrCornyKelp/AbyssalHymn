#ifndef INPUT_H
#define INPUT_H

#include <object2D.h>

class Input;
class Player;

struct KeyState
{
	SDL_Scancode code;
	// Standard
	bool moveset = 1; // If these are gameplay key or not
	bool state = 0;
	bool hold = 0;
	// Instant press
	int prepress;
	bool press();
	// Threshold
	int threshold = 0,
		threspeak = 0;
	bool threspass(int max);
	// Delay
	int keydelay = 0;

	long1D script;
	long1D script_history;

	void update(const Uint8* state, Input *input);

	string0D scriptHistoryToStr();
};

struct KeyTemplateN1
{
	KeyState
		moveU = {SDL_SCANCODE_W},
		moveD = {SDL_SCANCODE_S},
		moveL = {SDL_SCANCODE_A},
		moveR = {SDL_SCANCODE_D},
		proj = {SDL_SCANCODE_E},
		equip = {SDL_SCANCODE_Q},
		attack = {SDL_SCANCODE_F},
		jump = {SDL_SCANCODE_SPACE}, // FOR TESTING
		dash = {SDL_SCANCODE_LSHIFT};
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

struct MouseState
{
	int button = 0;
	bool state = 0;
	bool hold = 0;
	// Instant click
	bool click();
	int threshold = 0,
		threspeak = 0;
	bool threspass(int max);

	void update(Uint32 mousestate);
};

struct MouseMain
{
	MouseState
		// LEFT MOUSE
		L = {SDL_BUTTON_LEFT},
		// MIDDLE MOUSE
		M = {SDL_BUTTON_MIDDLE},
		// RIGHT MOUSE
		R = {SDL_BUTTON_RIGHT};
	// WHEEL STATE (-1: down, 1: up)
	short W = 0;
	// MOUSE POSITION
	int x = 0, y = 0;

	void update();

	int offMidX();
	int offMidY();
	int offPlayerX(Player *player);
	int offPlayerY(Player *player);
	int mapX(Player *player, short grid = 64);
	int mapY(Player *player, short grid = 64);
	bool inbox(ObjectBox mbox);
};

class Input 
{
public:
// ============================= KEYSTATE =======================

	KeyState
		// Gameplay
		moveU, moveD, moveL, moveR,
		proj, equip, attack,
		jump, dash,

		// Other
		lalt = {SDL_SCANCODE_LALT, 0},
		lctrl = {SDL_SCANCODE_LCTRL, 0},
		lshift = {SDL_SCANCODE_LSHIFT, 0},

		space = {SDL_SCANCODE_SPACE, 0},
		backspace = {SDL_SCANCODE_BACKSPACE, 0},

		arrowU = {SDL_SCANCODE_UP, 0},
		arrowD = {SDL_SCANCODE_DOWN, 0},
		arrowL = {SDL_SCANCODE_LEFT, 0},
		arrowR = {SDL_SCANCODE_RIGHT, 0},

		slash = {SDL_SCANCODE_SLASH, 0},
		backslash = {SDL_SCANCODE_BACKSLASH, 0},

		escape = {SDL_SCANCODE_ESCAPE, 0},

		// Function Key
		f1 = {SDL_SCANCODE_F1, 0},
		f2 = {SDL_SCANCODE_F2, 0},
		f3 = {SDL_SCANCODE_F3, 0},
		f4 = {SDL_SCANCODE_F4, 0},
		f5 = {SDL_SCANCODE_F5, 0},
		f6 = {SDL_SCANCODE_F6, 0};

	string0D script_history_full = "";
	bool script_active = 0;

// =========================== MOUSESTATE ==========================

	MouseMain mouse;

// =========================== INPUTFUNC ===========================

	int delay = 0;

	Input();
	void setTemplate(int keytemplate);
	void executeScript(string0D script_dir, bool from_cur = 0);
	void endScript();

	void updateMoveset();
	void updateOther();

	// ==================== OBSOLETE ======================

	SDL_GameController *controller;
};

#endif