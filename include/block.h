#ifndef BLOCK_H
#define BLOCK_H

#include "object2D.h"
#include "sprite.h"

class Block : public Object2D
{
private:
    // Sprite handler
    const char *spritePath;

    Sprite *blockSprite;

    bool isBlock = true;
    bool isCollideDown = true;

public:
    // using::Object2D; // Allow direct usage of Object2D's contructor
    Block(float X = 0, float Y = 0, int w = 64, int h = 64, bool collideDown = true);
    void initBlock(SDL_Renderer *renderer, const char* path);

    bool getCollideDown();

    void renderBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif