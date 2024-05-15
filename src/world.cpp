#include <world.h>

World::~World()
{
    SDL_DestroyTexture(BlackScreen);
    for (Map *map : MapVec) delete map;
}

World::World(std::vector<Map*> mapvec, int startmap) :
    MapVec(mapvec), MapCurrent(mapvec[startmap]), MapIndex(startmap)
{ MapCurrent->MapActive = 1; }

void World::initWorld(  Multiplayer *multi, Audio *audio,
                        Collision *collision, WorldLocation location)
{
    // Init Map
    for (int id = 0; id < MapVec.size(); id++)
        MapVec[id]->initMap(
            this, multi, audio, collision, id
        );
    // Init Player Spawn
    switchMap(location);
    // Init Music Track
    audio->createPlaylist(MapCurrent->MapPlaylist);

    // Useless Ah Stuff
    BlackScreen = Object2D::loadTexture("res/BlackScreen.png");
    SDL_SetTextureAlphaMod(BlackScreen, 0);
}

void World::setTransit(WorldLocation location, int trans_time)
{
    if (map_transition) return;

    if (location.index != -1 &&
        location.index != MapIndex &&
        !MapCurrent->MapPlaylist.comparePlaylist(
        MapVec[location.index]->MapPlaylist))
        MapCurrent->MapAudio->setPlistStop(1);

    map_transition = trans_time;
    map_transition_mid = trans_time / 2;
    transit_location = location;
}

void World::updateTransition()
{
    if (!map_transition) return;

    // Transition reach half point -> Start loading stuff
    map_transition--;
    if (int(map_transition) == int(map_transition_mid))
    {
        switchMap(transit_location);
        transit_location = {};
    }

    // Update Black Screen
    SDL_SetTextureAlphaMod(BlackScreen,
        255 * (1 - abs(float(map_transition / map_transition_mid) - 1))
    );
}

void World::updateWorld()
{ 
    CFG->WORLDTIME++;

    // This one is so out of place lmao
    updateTransition();

    // Update Current Map
    MapCurrent->updateMapActive();
    // Update Every Map
    for (Map *map : MapVec)
        map->updateMapGlobal();
}

void World::switchMap(WorldLocation location)
{
    // Create new audio track for new map
    if (location.index != -1 &&
        location.index != MapIndex)
        MapCurrent->MapAudio->createPlaylist(
            MapVec[location.index]->MapPlaylist
        );

    // If index = -1 then tp to self
    if (location.index != -1)
    {
        // Set Map Index
        MapIndex = location.index;
        // Set Maps Activity
        for (Map *map : MapVec)
            map->MapActive = 0;

        // Set Current Map
        MapCurrent = MapVec[MapIndex];
        MapCurrent->MapActive = 1;
    }

    MapCurrent->loadCheckpoint(location);
}