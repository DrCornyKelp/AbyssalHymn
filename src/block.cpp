#include "block.h"

// Constructor
Block::Block(float X, float Y, int w, int h, bool collideDown) : 
    Object2D(X, Y, w, h, w, h), isCollideDown(collideDown)
{}

void Block::initBlock(SDL_Renderer *renderer, const char* path)
{
    // Grid sprite
    blockSprite = new Sprite(getWidth(), getHeight(), 1, path);
    blockSprite->setTexture(Sprite::loadTexture(renderer, blockSprite->getSpritePath()));
}

bool Block::getCollideDown()
{
    return isCollideDown;
}

void Block::renderBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    int rel_x = focusX ? offsetX + getX() - px : getX();
    int rel_y = focusY ? offsetY + getY() - py : getY();

    SDL_Rect desRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2, getWidth(), getHeight()};
    SDL_RenderCopy(renderer, blockSprite->getTexture(), NULL, &desRect);
}