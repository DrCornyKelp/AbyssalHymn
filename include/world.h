#ifndef WORLD_H
#define WORLD_H

#include <map.h>

class World
{
public:
    // ======================== MAP =========================
    std::vector<Map*> MapVec;
    int MapIndex = 0;
    Map *MapCurrent;

    // ======== Cool Stuff That are oddly specific ==========
    WorldLocation transit_location;

    // ======== Standard Stuff (you know the drill) =========
    ~World();
    World(std::vector<Map*> mapvec, int startmap = 0);

    void initWorld( Multiplayer *multi, Audio *audio,
                    Collision *collision, WorldLocation location);

    void setTransit(WorldLocation location);
    void updateWorld();

    void switchMap(WorldLocation location);
};

#endif