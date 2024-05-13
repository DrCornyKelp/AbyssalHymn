#include <map.h>

// std::vector<MapTransit> deep_cavern_transit;

void SeaHorizonUpdate(Map *map) {
    if (map->MapActive)
    {
    // ============ CAN CAMERA RENDER ANYTHING OUTSIDE FOCUS BORDER ============
        map->MapMulti->MAIN->camera.outside_render = 0;

    // ======================== MAP TRANSITION TRIGGER =========================

        // for (MapTransit m_trans : deep_cavern_transit)
        // if (map->MapMulti->MAIN->insideGridBox(m_trans.box))
        // {
            // map->MapWorld->setTransit(m_trans.location);
            // break;
        // }

    // ======================== DYNAMIC CAMERA FOCUS =========================
    }
}