#include <map.h>

void Tutorial1Update(Map *map) {
    if (!map->Active) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->AUDIO->setPlistVolMax(100);
}