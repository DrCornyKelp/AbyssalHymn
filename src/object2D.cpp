#include <object2D.h>

Object2D::Object2D(float X, float Y, int w, int h) :
    x(X), y(Y),
    width(w), height(h)
{}

Object2D::Object2D(float X, float Y, int w, int h, int hw, int hh) : 
    x(X), y(Y),
    width(w), height(h),
    hit_w(hw), hit_h(hh)
{}

Object2D::Object2D(float X, float Y, int w, int h, int hw, int hh, int sw, int sh, int sim, int sfm, int si, int sf) : 
    x(X), y(Y),
    width(w), height(h),
    hit_w(hw), hit_h(hh),
    sprite_index_max(sim), sprite_frame_max(sfm),
    sprite_index(si), sprite_frame(sf),
    sprite_width(sw), sprite_height(sh)
{}

// Position
void Object2D::setX(float X) { x = X; }
void Object2D::setY(float Y) { y = Y; }
float Object2D::getX() { return x; }
float Object2D::getY() { return y; }

// Size / hitbox
void Object2D::setWidth(int w) { width = w; }
void Object2D::setHeight(int h) { height = h; }
void Object2D::setHitWidth(int hw) { hit_w = hw; }
void Object2D::setHitHeight(int hh) { hit_h = hh; }
int Object2D::getWidth() { return width; }
int Object2D::getHeight() { return height; }
int Object2D::getHitWidth() { return hit_w; }
int Object2D::getHitHeight() { return hit_h; }

// Combat hitbox
void Object2D::setCombatHitU(int hit) { combat_hit_up = hit; }
void Object2D::setCombatHitD(int hit) { combat_hit_down = hit; }
void Object2D::setCombatHitL(int hit) { combat_hit_left = hit; }
void Object2D::setCombatHitR(int hit) { combat_hit_right = hit; }
void Object2D::setCombatDamage(int dmg) { combat_damage = dmg; }
int Object2D::getCombatHitU() { return combat_hit_up; }
int Object2D::getCombatHitD() { return combat_hit_down; }
int Object2D::getCombatHitL() { return combat_hit_left; }
int Object2D::getCombatHitR() { return combat_hit_right; }
int Object2D::getCombatDamage() { return combat_damage; }

// Draw
void Object2D::setSprWidth(int sw) { sprite_width = sw; }
void Object2D::setSprHeight(int sh) { sprite_height = sh; }
void Object2D::setSprIndex(int si) { sprite_index = si; }
void Object2D::setSprIndexMax(int sim) { sprite_index_max = sim; }
void Object2D::setSprFrame(int sf) { sprite_frame = sf; }
void Object2D::setSprFrameMax(int sfm) { sprite_frame_max = sfm; }
int Object2D::getSprWidth() { return sprite_width; }
int Object2D::getSprHeight() { return sprite_height; }
int Object2D::getSprIndex() { return sprite_index; }
int Object2D::getSprIndexMax() { return sprite_index_max; }
int Object2D::getSprFrame() { return sprite_frame; }
int Object2D::getSprFrameMax() { return sprite_frame_max; }

// Speed / Accelaration
void Object2D::setVelX(float velX) { vel_x = velX; }
void Object2D::setVelY(float velY) { vel_y = velY; }
void Object2D::setAccelX(float accX) { accel_x = accX; }
void Object2D::setAccelY(float accY) { accel_y = accY; }
float Object2D::getVelX() { return vel_x; }
float Object2D::getVelY() { return vel_y; }
float Object2D::getAccelX() { return accel_x; }
float Object2D::getAccelY() { return accel_y; }

// Special Key
void Object2D::setSpecialKey(int key) { special_key = key; }
int Object2D::getSpecialKey() { return special_key; }

// VERY HELPFUL METHOD
void Object2D::objectStandardMovement()
{
    setX(getX() + getVelX());
    setY(getY() + getVelY());
    setVelX(getVelX() + getAccelX());
    setVelY(getVelY() + getAccelY());
};

void Object2D::objectSetSprite(bool end_lock)
{
    if (getSprIndexMax())
    {
        if (getSprFrame() < getSprFrameMax())
            setSprFrame(getSprFrame() + 1);
        else
        {
            setSprFrame(0);
            setSprIndex(getSprIndex() + 1);
        }

        if (getSprIndex() >= getSprIndexMax())
            if (end_lock)
                setSprIndex(getSprIndexMax() - 1);
            else
                setSprIndex(0);
    }
}