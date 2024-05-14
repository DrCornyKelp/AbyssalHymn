#ifndef CAMERA_H
#define CAMERA_H

class Player;
class Object2D;
class Multiplayer;
class Camera
{
private:

public:
    static bool renderIgnore(Player *player, Object2D *objSub, bool camIndependent = 0);

    // For drawing object relative to player
    static int objectDrawX(Player *player, Object2D *obj);
    static int objectDrawY(Player *player, Object2D *obj);
};

#endif