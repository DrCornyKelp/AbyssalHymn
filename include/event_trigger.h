#ifndef EVENT_TRIGGER_H
#define EVENT_TRIGGER_H

#include "object2D.h"
#include "sprite.h"

typedef void (*EventFunction)(int);

class EventTrigger : public Object2D
{
private:
    // Sprite handler
    const char *spritePath;

    Sprite *blockSprite;

    EventFunction event;

public:
    // using::Object2D; // Allow direct usage of Object2D's contructor
    EventTrigger(float X = 0, float Y = 0, int w = 64, int h = 64);
    void setEvent(EventFunction e);
    void triggerEvent(int player);
    void deleteEvent();
};

#endif