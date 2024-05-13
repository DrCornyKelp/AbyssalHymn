#include <audio_object.h>
#include <map.h>

AudioObject::AudioObject(string0D path, float X, float Y,
                        float R, float maxvolR, float overrideR) :
    Object2D(X, Y, 0, 0),
    radius(R),
    radius_max_vol(maxvolR),
    radius_override(overrideR)
{
    if (path == "") return;
    music.openFromFile(path);
    music.setLoop(1);
}

void AudioObject::updateProximity(Map *map)
{
    // Play if active
    if (map->MapActive &&
        music.getStatus() != sf::Music::Playing)
        music.play();
    if (!map->MapActive)
    {
        // Pause if not active
        if (music.getStatus() == sf::Music::Playing) 
            music.pause();
        // Ignore logic if not online
        return;
    }

    if (music.getPlayingOffset().asMilliseconds() >
        music.getDuration().asMilliseconds())
        play_once = true;

    float distant = distR(map->MapMulti->MAIN, this);

    float dr_ratio = (distant - radius_max_vol) / radius;
    volume = vol_max * (1 - (dr_ratio < 0 ? 0 : dr_ratio) );
    volume = volume > 0 ? volume : 0;

    // Update Map Bgm
    if (distant < radius)
    {
        if (distant > radius_override)
            map->MapAudio->setPlistVolMax(
                map->MapAudio->getPlistVolMax() * dr_ratio
            );
        else
            map->MapAudio->setPlistVolMax(0);
    }

    // Update current audio source
    music.setVolume(volume);
}

// ============================ FILE MANIPULATION ===================================

void AudioObject::appendAudioObject(Map *map, string0D a_dir)
{
    std::ifstream inputFile(a_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (line == "" ||
            line.back() == '#' ||
            line[0] ==  '#') continue;

        std::stringstream ss(line);
        char cm = ',';

        string0D audio_path;
        float X, Y, R, MVR, OR;

        std::getline(ss, audio_path, ',');
        ss>>X >> cm >> Y >> cm >> R >> cm >>
            MVR >> cm >> OR;

        AudioObject *aObj = new AudioObject(
            audio_path, X * 64 + 32, Y * 64 + 32,
            R * 64 + 32, MVR * 64 + 32, OR * 64 + 32
        );
        map->AudioObjVec.push_back(aObj);
    }
}