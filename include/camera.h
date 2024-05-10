#ifndef CAMERA_H
#define CAMERA_H

class Player;
class Object2D;
class Multiplayer;
class Camera
{
private:

public:
    static bool objectIgnore(Player *player, Object2D *objSub, bool camIndependent = 0);

    static int playerShiftX(Player *player);
    static int playerShiftY(Player *player);

    // For drawing object relative to player
    static int objectDrawX(Player *player, Object2D *obj);
    static int objectDrawY(Player *player, Object2D *obj);
    // For drawing object on top of player
    static int playerDrawX(Player *player, int W);
    static int playerDrawY(Player *player, int H);
};

#endif