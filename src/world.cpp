#include <world.h>

World::~World()
{
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
}

void World::setTransit(WorldLocation location)
{
    if (CFG->TRANSIT_EFFECT.fade) return;

    // Stop Current Map Track if different
    if (location.index != -1 &&
        location.index != MapIndex &&
        !MapCurrent->MapPlaylist.comparePlaylist(
        MapVec[location.index]->MapPlaylist))
        MapCurrent->MapAudio->setPlistStop(1);

    transit_location = location;
    CFG->TRANSIT_EFFECT.set(50, 50);
}

void World::updateWorld()
{ 
    CFG->WORLDTIME++;

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