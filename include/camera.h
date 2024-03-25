#ifndef CAMERA_H
#define CAMERA_H

#include <tuple>

#define DistXY std::tuple<int, int>
#define DistGet(result, index) std::get<index>(result)

class Player;
class Object2D;
class Camera
{
private:

public:
    static DistXY objectDistance(Object2D *objMain, Object2D *objSub);
    static bool objectOutBound(Player *player, Object2D *objSub);
    static void objectSetSprite(Object2D *obj, bool end_lock = 0);
    static int objectDrawX(Player *player, Object2D *obj);
    static int objectDrawY(Player *player, Object2D *obj);
};

#endif