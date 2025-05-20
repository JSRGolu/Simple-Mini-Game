#include "../../include/audio/SFXAudioManager.h"

void SFXAudioManager::playSound(const std::string& soundName, float volume)
{
    if (buffers.find(soundName) == buffers.end()) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile("sound/" + soundName + ".ogg")) {
            buffers[soundName] = buffer;
        }
    }
    activeSounds.emplace_back(buffers[soundName]);
    activeSounds.back().setVolume(volume);
    activeSounds.back().play();
}