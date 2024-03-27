#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <math.h>
#include <tuple>

#include <game.h>
#include <camera.h>
#include <sprite.h>
#include <audio.h>

class Object2D
{
private:
    int special_key = -1;

    // Size and position
    float x, y;
    int width, height;
    int hit_w, hit_h;

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
    int sprite_index, sprite_index_max;
    int sprite_frame, sprite_frame_max;

public:
    Object2D(float X, float Y, int w, int h);
    Object2D(float X, float Y, int w, int h, int hw, int hh);
    Object2D(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf);
    
    // Setters

    // Position
    void setX(float X);
    void setY(float Y);
    float getX();
    float getY();

    // Size / Hitbox
    void setWidth(int w);
    void setHeight(int h);
    void setHitWidth(int hw);
    void setHitHeight(int hh);
    int getWidth();
    int getHeight();
    int getHitWidth();
    int getHitHeight();

    // Comabt hitbox
    void setCombatHitU(int hit);
    void setCombatHitD(int hit);
    void setCombatHitL(int hit);
    void setCombatHitR(int hit);
    void setCombatDamage(int dmg);
    int getCombatHitU();
    int getCombatHitD();
    int getCombatHitL();
    int getCombatHitR();
    int getCombatDamage();

    // Speed / Accelaration

    // Simple movement, no extra logic
    void objectStandardMovement();
    void setVelX(float velX);
    void setVelY(float velY);
    void setAccelX(float accX);
    void setAccelY(float accY);
    float getVelX();
    float getVelY();
    float getAccelX();
    float getAccelY();

    // Drawing
    void setSprIndex(int si);
    void setSprIndexMax(int sim);
    void setSprFrame(int sf);
    void setSprFrameMax(int sfm);
    int getSprIndex();
    int getSprIndexMax();
    int getSprFrame();
    int getSprFrameMax();
    
    // Special Key for customizable value
    void setSpecialKey(int key);
    int getSpecialKey();
};

#endif