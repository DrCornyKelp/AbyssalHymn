#ifndef STAGE1_H
#define STAGE1_H

#include "stages.h"

class Stage1 : public Stages
{
private:
public:
    void initBlocks(SDL_Renderer *renderer) override;
    void initDecors(SDL_Renderer *renderer) override;
    void initEnemies(SDL_Renderer *renderer) override;
};

#endif