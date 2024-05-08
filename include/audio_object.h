#ifndef AUDIO_OBJECT_H
#define AUDIO_OBJECT_H

#include <object2D.h>

#define AudioObj1D std::vector<AudioObject*>

class Map;
class AudioObject : public Object2D
{
private:
    float radius = 0;
    float radius_override = 0;
    float radius_max_vol = 0;
    sf::Music music;

    bool play_once = 0;
    bool is_loop = 1;
    int volume = 0;
    int vol_max = 100;

public:
    AudioObject(std::string path, float X, float Y, float R,
                float maxvolR, float override);
    void updateProximity(Map *map);
    static void appendAudioObject(Map *map, std::string a_dir);
};

#endif