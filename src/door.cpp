#include <world.h>

// Destructor
Door::~Door() 
{ 
    SDL_DestroyTexture(door_texture);
    SDL_DestroyTexture(lock_texture);
}

// Read from file
Door::Door(DoorObject door) :
    Object2D(door.X*64 + 32, door.Y*64 + 64, 64, 128, 64, 128),
    style(door.style), handle_left(door.left),
    location(door.location), need_star(door.star)
{}
// Create from my ass
Door::Door( int style, bool h_left, int X, int Y,
            int m_index, int spawnX, int spawnY, int star) :
    Object2D(X*64 + 32, Y*64 + 64, 64, 128),
    location({m_index, spawnX, spawnY}), need_star(star)
{}

void Door::setStar(int star) { need_star = star; }
int Door::getStar() { return need_star; }

void Door::initDoor()
{ 
    // Some door are a bit more special (not standard door)
    if (style < 0) return;

    string0D h_dir = handle_left ? "L" : "R";
    door_texture = loadTexture(
        "res/Door/Door" + std::to_string(style) + h_dir + ".png"
    );
    lock_texture = loadTexture(
        "res/Door/DoorLock.png"
    );
}

// Enter the door
void Door::enterDoor(Map *map)
{
    if (Collision::playerCollision(map->MapPlayers->MAIN, this) &&
        map->MapPlayers->MAIN->state.on_ground &&
        map->MapPlayers->MAIN->getHitHeight() == 80 &&
        abs(map->MapPlayers->MAIN->getVelX()) < .2 &&
        map->MapInput->getKeyPress(0)
        // Star logic here
        )
    {
        map->MapInput->setKeyHold(0, true);
        map->MapWorld->setTransit(location);
    }
}

// Draw Door
void Door::draw(Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectIgnore(player, this) ||
        style < 0) return;

    // Draw Door
    SDL_Rect doorRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        64, 128};
    SDL_RenderCopy(CFG->RENDERER, door_texture, NULL, &doorRect);

    // Draw Lock
    if (!need_star) return;
    SDL_Rect lockRect = {Camera::objectDrawX(player, this) - 32,
                        Camera::objectDrawY(player, this),
                        128, 128};
    SDL_RenderCopy(CFG->RENDERER, lock_texture, NULL, &lockRect);
}

// ============================ FILE MANIPULATION ===================================

Door *Door::codeToDoorInfo(string0D str)
{
    std::stringstream ss(str);
    char cm = ',';

    int style; bool handle_left;
    int X, Y;
    int index, spawnX, spawnY;
    int star;

    ss  >> style >> cm >> handle_left >> cm >> X >> cm >> Y >> cm
        >> index >> cm >> spawnX >> cm >> spawnY >> cm
        >> star;

    DoorObject door_obj = { style, handle_left, X, Y,
                            {index, spawnX, spawnY}, star };

    Door *door = new Door(door_obj);
    door->initDoor();
    return door;
}

void Door::appendDoor(Map *map, string0D door_dir)
{
    std::ifstream inputFile(door_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {   
        // Empty or Comment => Skip
        if (line == "" ||
            line.back() == '#' ||
            line[0] ==  '#') continue;

        map->DoorVec.push_back(codeToDoorInfo(line));
    }
}