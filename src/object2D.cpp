#include "object2D.h"

Object2D::Object2D(float X, float Y, int w, int h, int hw, int hh) : 
    x(X), y(Y),
    width(w), height(h),
    hit_w(hw), hit_h(hh)
{}

Object2D::Object2D(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf) : 
    x(X), y(Y),
    width(w), height(h),
    hit_w(hw), hit_h(hh),
    sprite_index_max(sim), sprite_frame_max(sfm),
    sprite_index(si), sprite_frame(sf)
{}

// Setter
void Object2D::setX(float X)
{
    x = X;
}
void Object2D::setY(float Y)
{
    y = Y;
}
void Object2D::setWidth(int w)
{
    width = w;
}
void Object2D::setHeight(int h)
{
    height = h;
}
void Object2D::setHitWidth(int hw)
{
    hit_w = hw;
}
void Object2D::setHitHeight(int hh)
{
    hit_h = hh;
}
void Object2D::setSprIndex(int si)
{
    sprite_index = si;
}
void Object2D::setSprIndexMax(int sim)
{
    sprite_index_max = sim;
}
void Object2D::setSprFrame(int sf)
{
    sprite_frame = sf;
}
void Object2D::setSprFrameMax(int sfm)
{
    sprite_frame_max = sfm;
}

// Getter
float Object2D::getX()
{
    return x;
}
float Object2D::getY()
{
    return y;
}
int Object2D::getWidth()
{
    return width;
}
int Object2D::getHeight()
{
    return height;
}
int Object2D::getHitWidth()
{
    return hit_w;
}
int Object2D::getHitHeight()
{
    return hit_h;
}
int Object2D::getSprIndex()
{
    return sprite_index;
}
int Object2D::getSprIndexMax()
{
    return sprite_index_max;
}
int Object2D::getSprFrame()
{
    return sprite_frame;
}
int Object2D::getSprFrameMax()
{
    return sprite_frame_max;
}