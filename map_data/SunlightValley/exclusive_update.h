#include <map.h>

MapTransit1D SunlightValleyTransit;

void SunlightValleyUpdate(Map *map) {
    if (map->MapActive)
    {
    // ============ CAN CAMERA RENDER ANYTHING OUTSIDE FOCUS BORDER ============
        map->MapMulti->MAIN->camera.outside_render = 0;

    // ======================== MAP TRANSITION TRIGGER =========================

        for (MapTransit m_trans : SunlightValleyTransit)
        if (map->MapMulti->MAIN->insideGridBox(m_trans.box))
        {
            map->MapWorld->setTransit(m_trans.location);
            break;
        }

    // ======================== DYNAMIC CAMERA FOCUS =========================

        // if (map->MapMulti->MAIN->insideBox({11, 0, 0, 84}))     
        map->MapMulti->MAIN->camera.setCameraBorder(
            {0, 1, 1, 0}, {0, 0, 0, 0});
    }
}