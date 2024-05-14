#ifndef CAMERA_H
#define CAMERA_H

class Player;
class Object2D;
class Multiplayer;
class Camera
{
private:

public:
    // WORK IN PROGRESS
    // For drawing object relative to player
    static int objectDrawX(Player *player, Object2D *obj);
    static int objectDrawY(Player *player, Object2D *obj);

    // Object outside screen
    static bool outOfBound(SDL_Rect desRect);
    static bool outOfCam(Player *player, Object2D *obj);

};

#endif