#ifndef AUDIO_H
#define AUDIO_H

#include <object2D.h>

#define AudioSFX1D std::vector<AudioSFX>

class Map;
struct AudioSFX {
    sf::SoundBuffer buffer;
    sf::Sound sound;

    AudioSFX(const std::string& filePath);
    void play();
    bool isPlaying();
    static void shuffle(AudioSFX1D &sfx);
};

struct AudioPlaylist
{
    string1D paths;
    int1D delays;
    bool random = 0;

    // Music Track
    int m_cur = 0;
    int1D m_list;

    int delay = 0;

    void updatePlaylist(bool fresh = 0);
    bool comparePlaylist(AudioPlaylist other);
};

class Audio
{
private:
    bool stop = 0;
    // Volume
    int vol_cur = 100;
    int vol_max = 100;

    AudioPlaylist playlist;
    sf::Music music_cur;

public:
    ~Audio();
    Audio();

    // ============== BACKGROUND MUSIC ==============

    // Music Playlist
    void createPlaylist(AudioPlaylist alb);
    // Current Music
    void setPlistStop(bool s);
    void setPlistVolCur(int v);
    void setPlistVolMax(int v);
    bool getPlistStop();
    int getPlistVolCur();
    int getPlistVolMax();

    void updateTrack();
    static void appendMapPlaylist(Map *map, string0D t_dir);

    static bool isMusicPlaying(sf::Music &music);
    static bool isSoundPlaying(sf::Sound &sound);
};

#endif