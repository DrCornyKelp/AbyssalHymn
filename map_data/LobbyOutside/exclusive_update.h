#include <map.h>

void LobbyOutsideUpdate(Map *map)
{
    if (!map->MapActive) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->AUDIO->setPlistVolMax(100);
}