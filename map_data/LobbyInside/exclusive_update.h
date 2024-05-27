#include <map.h>

void LobbyInsideUpdate(Map *map)
{
    if (!map->MapActive) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->AUDIO->setPlistVolMax(30);
}