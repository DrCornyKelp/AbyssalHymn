#include "block.h"

// Constructor
Block::Block(float X, float Y, int w, int h) : 
    Object2D(X, Y, w, h, w, h)
{}

void Block::initBlock(SDL_Renderer *renderer)
{
    // Grid sprite
    setHitWidth(getWidth());
    setHitHeight(getHeight());
    blockSprite = new Sprite(getWidth(), getHeight(), 1, "res/BlockTile/Grass.png");
    blockSprite->setTexture(Sprite::loadTexture(renderer, blockSprite->getSpritePath()));
}

void Block::setCollisionUnder(bool colli)
{
    collisionUnder = colli;
}
bool Block::getCollisionUnder()
{
    return collisionUnder;
}

void Block::renderBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    int rel_x = focusX ? offsetX + getX() - px : getX();
    int rel_y = focusY ? offsetY + getY() - py : getY();

    SDL_Rect desRect = {rel_x - getWidth() / 2, 720 - rel_y - getHeight() / 2, getWidth(), getHeight()};

    // SDL_Rect desRect = {int(getX()), int(getY()), getSprSize(), getSprSize()};
    SDL_RenderCopy(renderer, blockSprite->getTexture(), NULL, &desRect);
}