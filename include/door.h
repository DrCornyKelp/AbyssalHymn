#ifndef DOOR_H
#define DOOR_H

#include <object2D.h>

#define Door1D std::vector<Door*>

struct WorldLocation
{ 
    int index, sX, sY;
    bool snap = 0;
};

struct MapTransit
{
    ObjectBox box;
    WorldLocation location;
};

struct DoorObject
{
    int style, left;
    int X, Y;
    WorldLocation location;
    int star;
};

class Map;
class World;
class Player;
class Door : public Object2D
{
private:
    int style = 0;
    bool handle_left = 0;
    WorldLocation location;

    // DOOOR STUCK, DOOR STUCKKKK, PLEASE I BEG YOU
    int need_star = 0;
    int lock_alpha = 0;

    SDL_Texture *door_texture, *lock_texture;

public:
    ~Door();
    Door(DoorObject door);
    Door(int style, bool h_left, int X, int Y,
        int m_index, int spawnX, int spawnY,
        int star = 0);

    void setStar(int star);
    int getStar();

    void initDoor();
    void enterDoor(Map *map);
    void draw(Player *player);

    static Door *codeToDoorInfo(string0D str);
    static void appendDoor(Map *map, string0D door_dir);
};

#endif