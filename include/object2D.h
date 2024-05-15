#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <configuration.h>
#include <camera.h>

#define ObjectBox1D std::vector<ObjectBox>
#define ObjectBox2D std::vector<ObjectBox1D>
#define ObjectBox3D std::vector<ObjectBox2D>

struct ObjectXY { int x = 0, y = 0; };
struct ObjectXYb { bool x = 0, y = 0; };
struct ObjectXYf { float x = 0, y = 0; };
struct ObjectHitbox
{
    float x = 0, y = 0;
    float w = 0, h = 0;
    int hw = w, hh = h;

    ObjectHitbox hitboxGrid(int gr = 64);
    void grid(int gr = 64);
};
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
struct ObjectCombatHit
{ int up = 0, down = 0, left = 0, right = 0, dmg = 0; };
struct ObjectSprite
{
    int sw = 0, sh = 0;
    int sim = 0, sfm = 0;
    int si = 0, sf = 0;
};
struct ObjectMovement
{
    float vel_x = 0, vel_y = 0;
    float accel_x = 0, accel_y = 0;
};

class Object2D
{
private:
    int special_key = -1;

    // Size and position
    float x = 0, y = 0;
    int width = 0,
        height = 0;
    int hit_w = 0,
        hit_h = 0;

    // Speed
    float vel_x = 0, vel_y = 0;
    float accel_x = 0, accel_y = 0;

    // Combat (if possible)
    int combat_hit_up = 0;
    int combat_hit_down = 0;
    int combat_hit_left = 0;
    int combat_hit_right = 0;
    int combat_damage = 0;

    // Sprites handling
    int sprite_index = 0,
        sprite_index_max = 0;
    int sprite_row = 0,
        sprite_row_max = 0,
        sprite_row_repeat = 0;
    int sprite_frame = 0,
        sprite_frame_max = 0;
    int sprite_width = 0,
        sprite_height = 0;

    // Ignore Object Existance
    bool ignore = 0;

    // Camera Dependencey
    bool cam_depend = true;

public:
    ~Object2D(); // Default Destructor
    Object2D(); // Default Constructor
    Object2D(ObjectHitbox box, ObjectSprite sprite = {}, ObjectMovement movement = {});
    Object2D(float X, float Y, int w, int h);
    Object2D(float X, float Y, int w, int h, int hw, int hh);
    Object2D(float X, float Y, int w, int h, int hw, int hh,
            int sw, int sh, int sim, int sfm, int si = 0, int sf = 0);

    // Ignore Drawing
    bool getIgnore();
    void setIgnore(bool ignore);

    // Camera Independent
    bool getCamDepend();
    void setCamDepend(bool depend);

    // Position
    void setX(float X);
    void setY(float Y);
    float getX();
    float getY();
    int getGridX();
    int getGridY();
    int getGridLX();
    int getGridRX();
    int getGridTY();
    int getGridBY();

    // Size / Hitbox
    void setWidth(int w);
    void setHeight(int h);
    void setHitWidth(int hw);
    void setHitHeight(int hh);
    int getWidth();
    int getHeight();
    int getGridWidth(bool getExtend = 0);
    int getGridHeight(bool getExtend = 0);
    int getHitWidth();
    int getHitHeight();

    // Comabt hitbox
    void setCombatHit(ObjectCombatHit c_hit);
    void setCombatHitU(int hit);
    void setCombatHitD(int hit);
    void setCombatHitL(int hit);
    void setCombatHitR(int hit);
    void setCombatDamage(int dmg);
    ObjectCombatHit getCombatHit();
    int getCombatHitU();
    int getCombatHitD();
    int getCombatHitL();
    int getCombatHitR();
    int getCombatDamage();

    // Speed / Accelaration

    // Simple movement, no extra logic
    void setVelX(float velX);
    void setVelY(float velY);
    void setAccelX(float accX);
    void setAccelY(float accY);
    float getVelX();
    float getVelY();
    float getAccelX();
    float getAccelY();

    // Drawing
    void setSprWidth(int sw);
    void setSprHeight(int sh);
    void setSprIndex(int si);
    void setSprIndexMax(int sim);
    void setSprRow(int sr);
    void setSprRowMax(int srm);
    void setSprRowRepeat(int srr);
    void setSprFrame(int sf);
    void setSprFrameMax(int sfm);
    int getSprWidth();
    int getSprHeight();
    int getSprIndex();
    int getSprIndexMax();
    int getSprRow();
    int getSprRowMax();
    int getSprRowRepeat();
    int getSprFrame();
    int getSprFrameMax();

    // Box
    bool insideBox(ObjectBox box);
    bool insideGridBox(ObjectBox gridbox);
    ObjectBox getBox();

    // Special Key for customizable value
    void setSpecialKey(int key);
    int getSpecialKey();

    // =================== VERY HELPFUL METHOD ======================

    // Note!!!: dist is a vector in both direction,
    // not the absolute value
    static int distX(Object2D *obj1, Object2D *obj2, bool absolute = 0);
    static int distY(Object2D *obj1, Object2D *obj2, bool absolute = 0);
    static int distBorderX(Object2D *obj1, Object2D *obj2);
    static int distBorderY(Object2D *obj1, Object2D *obj2);
    static int distR(Object2D *obj1, Object2D *obj2);

    static bool objectIgnore(Object2D *objMain, Object2D *objSub);

    static SDL_Texture *loadTexture(string0D path);
    static SDLTexture1D loadTextures(string0D path, int max);
    static void deleteTextures(SDLTexture1D textures);

    bool objectSetSprite(bool end_lock = 0);

    void objectStandardMovement(bool lock_vel = 0);
    float1D objectPredictMovement();
};

#endif