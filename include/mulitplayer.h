#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <player.h>

struct PlayerCamera
{
    Multiplayer *multiplayer;
    int offset_mid_x = 0;
    int offset_mid_y = 0;
    bool unfocus_x = 0;
    bool unfocus_y = 0;
    short unfocus_direction_y = 0; // 1 : up, -1: down
    int unfocus_offset_x = 0;
    int unfocus_offset_y = 0;

    // Goal Value
    ObjectBox focus_dir;
    ObjectBox focus_point;
    ObjectBox focus_border;
    bool outside_render = true;
    // Progress Value
    ObjectBox focus_true;
    int focus_speed = 4;
    bool focus_snap = 0;

    // Camera Effect
    float ease_x = 0;
    float ease_y = 0;
    float effect_x = 0;
    float effect_y = 0;

    // Vertical ahead
    int vertical_ahead_time = 0;
    int vertical_ahead_time_max = 150;
    float vertical_ahead = 0;
    float vertical_ahead_max = 192;

    int getFocusTriggerX();
    int getFocusTriggerY();

    void resetCamera();
    void setCameraBorder(ObjectBox f_dir, ObjectBox f_val);
    void setCameraFocus(ObjectBox f_dir, ObjectBox f_val, short gr);
    void playerCameraFocus();
    void playerCameraProperty(Input *input);
};

class Multiplayer
{
public:
    PlayerCamera camera = {this};
    Player1D PlayerVec;

    Multiplayer(Player1D playervec);
};

#endif