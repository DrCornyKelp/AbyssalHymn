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

    // ======================== TIME ========================
    int WorldTime = 0;
    int WorldDay = 0;

    // ======== Cool Stuff That are oddly specific ==========
    SDL_Texture *BlackScreen;
    WorldLocation transit_location;
    float map_transition = 0;
    float map_transition_mid = 0;

    // ======== Standard Stuff (you know the drill) =========
    ~World();
    World(std::vector<Map*> mapvec, int startmap = 0);

    void initWorld( Multiplayer *multi, Audio *audio,
                    Collision *collision, WorldLocation location);

    void setTransit(WorldLocation location, int trans_time = 30);
    void updateTransition();
    void updateWorld();

    void switchMap(WorldLocation location);
};

#endif