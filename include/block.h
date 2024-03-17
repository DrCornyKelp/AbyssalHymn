#ifndef BLOCK_H
#define BLOCK_H

#include "game.h"
#include "object2D.h"
#include "sprite.h"

class Block : public Object2D
{
private:
    // Sprite handler
    const char *sprite_path;
    Sprite *block_sprite;

    bool isBlock = true;
    bool isCollideDown = true;

public:
    // using::Object2D; // Allow direct usage of Object2D's contructor
    Block(const char* sPath, float X = 0, float Y = 0, float w = 64, float h = 64, int grid = 32, bool collideDown = true);
    void initBlock(SDL_Renderer *renderer);

    bool getCollideDown();

    void renderBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif