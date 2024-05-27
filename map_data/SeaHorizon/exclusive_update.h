#include <map.h>

// std::vector<MapTransit> deep_cavern_transit;

void SeaHorizonUpdate(Map *map) {
    if (map->Active)
    {
    // ============ CAN CAMERA RENDER ANYTHING OUTSIDE FOCUS BORDER ============
        map->MULTI->MAIN->camera.outside_render = 0;

    // ======================== MAP TRANSITION TRIGGER =========================

        // for (MapTransit m_trans : deep_cavern_transit)
        // if (map->MULTI->MAIN->insideGridBox(m_trans.box))
        // {
            // map->WORLD->setTransit(m_trans.location);
            // break;
        // }

    // ======================== DYNAMIC CAMERA FOCUS =========================
    }
}