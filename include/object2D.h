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
    float vel_x, vel_y;
    float accel_x, accel_y;

    // Combat (if possible)


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

    // Speed
    void setVelX(float velX);
    void setVelY(float velY);
    float getVelX();
    float getVelY();

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