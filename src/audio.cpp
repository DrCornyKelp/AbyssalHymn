#include <map.h>

// ============== AUDIO SFX ==================

AudioSFX::AudioSFX(const std::string& filePath)
{
    buffer.loadFromFile(filePath);
    sound.setBuffer(buffer);
}
void AudioSFX::play()
{
    sound.play();
}
bool AudioSFX::isPlaying()
{
    return sound.getStatus() == sf::Sound::Playing;
}
void AudioSFX::shuffle(AudioSFX1D &sfx)
{
    std::random_shuffle(sfx.begin(), sfx.end());
}

// ============== AUDIO PLAYLIST ==============

void AudioPlaylist::updatePlaylist(bool fresh)
{
    // Move on to next track on the playlist
    if (!fresh)
    {
        // Set a delay
        delay = delays[m_cur];
        // Increment playlist index
        m_cur++;
        // Reupdate playlist condition
        if (m_cur < paths.size()) return;
    }

    // Reupdate playlist
    m_cur = 0;
    if (random) m_list = CFG->randomInt1D(paths.size());
    else        m_list = CFG->randomInt1D(paths.size(), 0, 0);
}

bool AudioPlaylist::comparePlaylist(AudioPlaylist other)
{
    if (paths.size() != other.paths.size() ||
        random != other.random) return 0;

    for (int p = 0; p < paths.size(); p++)
        if (paths[p] != other.paths[p] ||
            delays[p] != other.delays[p])
            return 0;

    return 1;
}

Audio::~Audio() { music_cur.stop(); }
Audio::Audio() {};

void Audio::createPlaylist(AudioPlaylist plist)
{
    // Reset Current Album
    if (plist.paths == playlist.paths) return;

    playlist = plist;
    playlist.updatePlaylist(true);

    // Reset Current Music
    stop = 0;
    music_cur.stop();
    music_cur.openFromFile(
        playlist.paths[playlist.m_list[playlist.m_cur]]
    );
}

void Audio::setPlistStop(bool s) { stop = s; }
void Audio::setPlistVolCur(int v) { vol_cur = v; }
void Audio::setPlistVolMax(int v) { vol_max = v; }
bool Audio::getPlistStop() { return stop; }
int Audio::getPlistVolCur() { return vol_cur; }
int Audio::getPlistVolMax() { return vol_max; }

void Audio::updateTrack()
{
    // Empty Play List -> Ignore
    if (!playlist.paths.size()) return;

    // Stopping/Playing Volume Transition
    if ((stop && vol_cur > 0) ||
        (vol_cur > vol_max))
        vol_cur -= 4;
    if (!stop && vol_cur < vol_max)
        vol_cur += 4;
    music_cur.setVolume(vol_cur);

    if (stop && vol_cur <= 4) return;

    // Delay between every track
    if (playlist.delay)
    { playlist.delay--; return; }

    // Music is playing => No update yet
    if (isMusicPlaying(music_cur)) return;

    // Open New Music Once Done
    music_cur.openFromFile(
        playlist.paths[playlist.m_list[playlist.m_cur]]
    );
    music_cur.play();

    // Update playlist
    playlist.updatePlaylist();
}

void Audio::appendMapPlaylist(Map *map, string0D t_dir)
{
    std::ifstream inputFile(t_dir);
    string0D line;

    AudioPlaylist newAlbum;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (CFG->isComment(line)) continue;

        std::stringstream ss(line);

        string0D t_path;
        string0D t_delay;

        std::getline(ss, t_path, ',');
        std::getline(ss, t_delay, ',');

        // Playlist Randomized?
        if (line[0] == '*')
        { newAlbum.random = 1; break; }

        newAlbum.delays.push_back(stoi(t_delay));
        newAlbum.paths.push_back(t_path);
    }

    map->MapPlaylist = newAlbum;
}

bool Audio::isMusicPlaying(sf::Music &music)
{
    return music.getStatus() == sf::Music::Playing;
}
bool Audio::isSoundPlaying(sf::Sound &sound)
{
    return sound.getStatus() == sf::Sound::Playing;
}