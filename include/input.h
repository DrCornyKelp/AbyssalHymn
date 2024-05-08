#ifndef INPUT_H
#define INPUT_H

#include <object2D.h>

class Player;
class Input 
{
private:
	// Input
	bool1D key, click = {0, 0};
	bool1D keyhold, clickhold = {0, 0};

	int1D keythreshold;
	int1D clickthreshold = {0, 0};

	int1D keythrespeak;
	int1D clickthrespeak = {0, 0};

	// -1: Scroll Down, 1: Scroll Up
	short wheel = 0;

	// Note:
	// mouse_x start from left
	// mouse_y start from bottom
	int mouse_x, mouse_y;

	// 0: up
	// 1: down
	// 2: left
	// 3: right
	// 4: jump
	// 5: dash
	// 6: attack
	// 7: swap
	// 8: throw
	// 9: command
	// 10: editor menu
	// 11: up arrow
	// 12: down arrow
	// 13: left arrow
	// 14: right arrow
	SDL_GameController *controller;

	int key_delay = 0;
	int click_delay = 0;
	SDL_Event event;
public:
	void initInput();
	bool input();

	// Keyboard/Controller
	void setKeyDelay(int delay);
	void setKeyHold(int i, bool held);
	bool getKeyHold(int i);
	bool getKeyPress(int i);
	bool getKeyThreshold(int i, int max);
	int getKeyThresValue(int i);
	int getKeyThresPeak(int i);
	void resetKeyThresPeak(int i);

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