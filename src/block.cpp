#include "block.h"

// Constructor
Block::Block(const char* sPath, float X, float Y, float w, float h, int grid, bool moving) : 
    Object2D((X + w/2) * grid, (Y + h/2) * grid,
            w * grid, h * grid, w * grid, h * grid),
    sprite_path(sPath), isMoving(moving)
{}

void Block::initBlock(SDL_Renderer *renderer)
{
    // Grid sprite
    block_sprite = new Sprite(getWidth(), getHeight(), 1, sprite_path);
    block_sprite->setTexture(Sprite::loadTexture(renderer, block_sprite->getSpritePath()));
    delete sprite_path;
}

// Setter
void Block::setMoving(bool move)
{
    isMoving = move;
}
void Block::setStepOn(bool step)
{
    isStepOn = step;
}
void Block::setOutBound(bool oob)
{
    isOutBound = oob;
}
void Block::setHugged(short hug)
{
    isHugged = hug;
}
void Block::setVelX(float vx)
{
    vel_x = vx;
}
void Block::setVelY(float vy)
{
    vel_y = vy;
}

// Getter
bool Block::getMoving()
{
    return isMoving;
}
bool Block::getStepOn()
{
    return isStepOn;
}
bool Block::getOutBound()
{
    return isOutBound;
}
short Block::getHugged()
{
    return isHugged;
}
float Block::getVelX()
{
    return vel_x;
}
float Block::getVelY()
{
    return vel_y;
}

void Block::updateBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    if (vel_x != 0 || vel_y != 0)
    {
        isMoving = true;
        setX(getX() + vel_x);
        setY(getY() + vel_y);
    }

    if (!isOutBound)
    {
        int rel_x = focusX ? offsetX + getX() - px : getX();
        int rel_y = focusY ? offsetY + getY() - py : getY();

        SDL_Rect desRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2, getWidth(), getHeight()};
        SDL_RenderCopy(renderer, block_sprite->getTexture(), NULL, &desRect);
    }
}