#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <vector>

class Input 
{
private:
    // Input
    std::vector<bool> button;   // 0: up
                                // 1: down
                                // 2: left
                                // 3: right
                                // 4: jump
                                // 5: dash
                                // 6: attack
                                // 7: swap
                                // 8: throw
                                // 9: grid
                                // 10: dev
                                // 11: pause
public:
    void initInput();
    bool input(SDL_GameController *controller);
    bool getButton(int i);
};

#endif