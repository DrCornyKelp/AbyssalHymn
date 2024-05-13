#include <map.h>

MapTransit1D tutorial_4_transit = {
    {{6, 5, 68, 68}, {1, 2, 5}}
};

ObjectBox1D tutorial_4_camera_box = {
    {11, 0, 0, 68},
};

void Tutorial4Update(Map *map) {
    if (map->MapActive)
    {
    // ============ CAN CAMERA RENDER ANYTHING OUTSIDE FOCUS BORDER ============
        map->MapMulti->MAIN->camera.outside_render = 0;

    // ======================== MAP TRANSITION TRIGGER =========================

        for (MapTransit m_trans : tutorial_4_transit)
        if (map->MapMulti->MAIN->insideGridBox(m_trans.box))
        {
            map->MapWorld->setTransit(m_trans.location);
            break;
        }

    // ======================== DYNAMIC CAMERA FOCUS ===========================

        for (ObjectBox f_cam_box : tutorial_4_camera_box)
        if (map->MapMulti->MAIN->insideGridBox(f_cam_box))
        {
            map->MapMulti->MAIN->camera.setCameraBorder(
            {1, 1, 1, 1}, f_cam_box);
            break;
        }
    }

    // ======================== UPDATE AUDIO PROPERTIES ========================
    map->MapAudio->setPlistVolMax(100);
}