#include <map.h>

void LobbyInsideUpdate(Map *map)
{
    if (!map->Active) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->AUDIO->setPlistVolMax(30);
}