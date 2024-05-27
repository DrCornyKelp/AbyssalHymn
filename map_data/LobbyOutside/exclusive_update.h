#include <map.h>

void LobbyOutsideUpdate(Map *map)
{
    if (!map->Active) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->AUDIO->setPlistVolMax(100);
}