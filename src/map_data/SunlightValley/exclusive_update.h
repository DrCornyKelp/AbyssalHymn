#include <map.h>

MapTransit1D SunlightValleyTransit;

void SunlightValleyUpdate(Map *map) {
    if (map->MapActive)
    {
    // ============ CAN CAMERA RENDER ANYTHING OUTSIDE FOCUS BORDER ============
        map->MapPlayer->camera.outside_render = 0;

    // ======================== MAP TRANSITION TRIGGER =========================

        for (MapTransit m_trans : SunlightValleyTransit)
        if (map->MapPlayer->insideGridBox(m_trans.box))
        {
            map->MapWorld->setTransit(m_trans.location);
            break;
        }

    // ======================== DYNAMIC CAMERA FOCUS =========================

        // if (map->MapPlayer->insideBox({11, 0, 0, 84}))     
        map->MapPlayer->camera.setCameraBorder(
            {0, 1, 1, 0}, {0, 0, 0, 0});
    }
}