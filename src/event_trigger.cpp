#include "event_trigger.h"

EventTrigger::EventTrigger(float X, float Y, int w, int h) : 
    Object2D(X, Y, w, h, w, h)
{}

void EventTrigger::setEvent(EventFunction e)
{
    event = e;
}

void EventTrigger::triggerEvent(int player)
{
    event(player);
    deleteEvent();
}

void EventTrigger::deleteEvent()
{
    delete this;
}