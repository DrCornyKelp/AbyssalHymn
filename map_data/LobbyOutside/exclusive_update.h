#include <map.h>

void LobbyOutsideUpdate(Map *map)
{
    if (!map->MapActive) return;

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->MapAudio->setPlistVolMax(100);
}