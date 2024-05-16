#ifndef WORLD_H
#define WORLD_H

#include <map.h>

class World
{
public:
    // =============== SOME GLOBAL COMPONENT ================
    Multiplayer *MULTI;
    Audio *AUDIO;
    Collision *COLLI;

    // ======================== MAP =========================
    Map1D MapVec;
    Map *MapCur;
    int MapIndex = 0;

    // ======== Cool Stuff That are oddly specific ==========
    WorldLocation transit_location;

    // ======== Standard Stuff (you know the drill) =========
    ~World();
    World(Map1D mapvec, int startmap = 0);

    void initWorld(Multiplayer *multi, Audio *audio, Collision *collision);

    void setTransit(WorldLocation location);
    void updateWorld();

    void switchMap(WorldLocation location);
};

#endif