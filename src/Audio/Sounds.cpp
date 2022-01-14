/*
** EPITECH PROJECT, 2021
** B-YEP-400-MPL-4-1-indiestudio-cyril.grosjean
** File description:
** Sounds
*/

#ifdef __unix
    #define OS_Windows 0
    #define MUSIC_PLAYING IsMusicStreamPlaying
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows 1
    #define MUSIC_PLAYING IsMusicPlaying
#endif

#include "Sounds.hpp"

IS::Sounds::Sounds(const std::string &soundPath, bool looping)
{
    std::string path = soundPath;
    if (std::filesystem::exists(path)) {
        _music = LoadMusicStream(path.c_str());
        _music.looping = looping;
    } else if (std::filesystem::exists((path = ASSETS_PATH"ressources/" + soundPath))) {
        _music = LoadMusicStream(path.c_str());
        _music.looping = looping;
    }
}

IS::Sounds::~Sounds()
{
}

void IS::Sounds::play()
{
    if (MUSIC_PLAYING(_music))
        StopMusicStream(_music);
    PlayMusicStream(_music);
}

void IS::Sounds::stop()
{
    StopMusicStream(_music);
}

void IS::Sounds::setLooping(bool loop)
{
    _music.looping = loop;
}

Music IS::Sounds::getMusic() const
{
    return (_music);
}
