#ifndef RENDERER_H
#define RENDERER_H

#include <scene.h>
#include <hud.h>
#include <world.h>

class Renderer
{
private:

public:
    void renderGameplay(Map *map, Hud *hud);
    void renderMainMenu(Scene *main_menu);
    void renderLevelSelectMenu(Scene *main_menu);
};

#endif