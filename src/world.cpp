#include <world.h>

World::~World()
{ 
    // Delete Every Map
    // (And their component ofc cant forget pointer management)
    for (Map *map : MapVec) delete map;
    // Delete Other Component
    delete MULTI, AUDIO, COLLI;
}

World::World(std::vector<Map*> mapvec, int startmap) :
    MapVec(mapvec), MapCurrent(mapvec[startmap]), MapIndex(startmap)
{ MapCurrent->MapActive = 1; }

void World::initWorld(Multiplayer *multi, Audio *audio, Collision *collision)
{
    // Init Some Component
    MULTI = multi;
    AUDIO = audio;
    COLLI = collision;

    // Init Map
    for (int id = 0; id < MapVec.size(); id++)
        MapVec[id]->initMap(
            this, multi, audio, collision, id
        );
    // Init Music Track
    audio->createPlaylist(MapCurrent->MapPlaylist);
}

void World::setTransit(WorldLocation location)
{
    if (CFG->TRANSIT_EFFECT.active) return;

    // Stop Current Map Track if different
    if (location.index != -1 &&
        location.index != MapIndex &&
        !MapCurrent->MapPlaylist.comparePlaylist(
        MapVec[location.index]->MapPlaylist))
        MapCurrent->MapAudio->setPlistStop(1);

    transit_location = location;
    CFG->TRANSIT_EFFECT.set(20, 10);
}

void World::updateWorld()
{ 
    CFG->WORLDTIME++;

    // Update Transition Transit
    if (CFG->TRANSIT_EFFECT.midpoint() &&
        !transit_location.invalid)
    {
        switchMap(transit_location);
        transit_location.invalid = 1;
    }

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