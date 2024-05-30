#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <configuration.h>
#include <camera.h>

#define ObjectBox1D std::vector<ObjectBox>
#define ObjectBox2D std::vector<ObjectBox1D>
#define ObjectBox3D std::vector<ObjectBox2D>

struct ObjectXY { int x = 0, y = 0; };
struct ObjectXYb { bool x = 0, y = 0; };
struct ObjectXYs { short x = 0, y = 0; };
struct ObjectXYf { float x = 0, y = 0; };
struct ObjectXYWH { int x = 0, y = 0, w = 0, h = 0; };
struct ObjectHitbox
{
    float x = 0, y = 0;
    int w = 0, h = 0,
        hw = 0, hh = 0;

    ObjectHitbox hitboxGrid(int gr = 64);
    void grid(int gr = 64);

    int gridX();
    int gridY();
    int gridLX();
    int gridRX();
    int gridBY();
    int gridTY();

    int gridW(bool getExtend = 0);
    int gridH(bool getExtend = 0);
};

struct ObjectSprite
{
    // Standard Sprite
    int sw = 0, sh = 0;
    int sim = 0, sfm = 0;
    // Sprite Row
    int srm = 0, srr = 0;
    // Runtime Value
    int si = 0, sr = 0, sf = 0;
};

struct ObjectMovement
{
    float vel_x = 0, vel_y = 0;
    float accel_x = 0, accel_y = 0;
};

struct ObjectVel
{ float x = 0, y = 0; };

struct ObjectAccel
{ float x = 0, y = 0; };

struct ObjectBox
{ 
    int up = -1, down = -1,
        left = -1, right = -1;
    // Some Method
    ObjectBox boxGrid(int gr = 64);
    void grid(int gr = 64);
    void reorder();
    void copy(ObjectBox box);
    bool compare(ObjectBox box);
    bool contain(int x, int y);
    ObjectHitbox hitbox();
};
struct ObjectCombatBox
{ int up = 0, down = 0, left = 0, right = 0, dmg = 0; };

class Object2D
{
public:
    int special_key = -1;

    // Size and position
    ObjectHitbox hitbox;
    // Sprite
    ObjectSprite sprite;
    // Speed
    ObjectVel vel;
    ObjectAccel accel;

    // Combat (if possible)
    ObjectCombatBox combatbox;

    // Ignore Object Existance
    bool ignore = 0;

    // Camera Dependencey
    bool cam_depend = true;

    ~Object2D(); // Default Destructor
    Object2D(); // Default Constructor
    Object2D(ObjectHitbox box, ObjectSprite spr = {}, ObjectVel v = {}, ObjectAccel a = {});

    // Box
    bool insideBox(ObjectBox box);
    bool insideGridBox(ObjectBox gridbox);
    ObjectBox getBox();

    // =================== VERY HELPFUL METHOD ======================

    // Note!!!: dist is a vector in both direction,
    // not the absolute value
    static int distX(Object2D *obj1, Object2D *obj2, bool absolute = 0);
    static int distY(Object2D *obj1, Object2D *obj2, bool absolute = 0);
    static int distBorderX(Object2D *obj1, Object2D *obj2);
    static int distBorderY(Object2D *obj1, Object2D *obj2);
    static int distR(Object2D *obj1, Object2D *obj2);

    static ObjectBox SDLRectToBox(SDL_Rect rect);
    static SDL_Rect BoxToSDLRect(ObjectBox box);

    static bool objectIgnore(Object2D *objMain, Object2D *objSub);

    static void deleteTextures(SDLTexture1D textures);

    bool setSprite(bool end_lock = 0);
    static void objectSetSprite(ObjectSprite &sprite);

    void objectStandardMovement(bool lock_vel = 0);
    float1D objectPredictMovement();
};

#endif