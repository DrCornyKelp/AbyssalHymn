#include <map.h>

void Tutorial2Update(Map *map) {
    if (!map->MapActive) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->MapAudio->setPlistVolMax(100);
}