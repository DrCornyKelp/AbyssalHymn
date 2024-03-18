#ifndef BLOCK_H
#define BLOCK_H

#include "game.h"
#include "object2D.h"
#include "sprite.h"
#include "decoration.h"

class Block : public Object2D
{
private:
    // Sprite handler
    const char *sprite_path;
    Sprite *block_sprite;

    bool isMoving;
    bool isStepOn = false;
    short isHugged = 0;
    bool isOutBound = false;
    float vel_x = 0, vel_y = 0;

public:
    // using::Object2D; // Allow direct usage of Object2D's contructor
    Block(const char* sPath, float X = 0, float Y = 0, float w = 1, float h = 1, int grid = 64, bool moving = false);
    void initBlock(SDL_Renderer *renderer);

    void setMoving(bool move);
    void setStepOn(bool step);
    void setOutBound(bool oob);
    void setHugged(short hug);
    void setVelX(float X);
    void setVelY(float Y);

    bool getMoving();
    bool getStepOn();
    bool getOutBound();
    short getHugged();
    float getVelX();
    float getVelY();

    void updateBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif