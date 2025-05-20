#pragma once
#include "AudioManager.h"
#include <SFML/Audio.hpp>
#include <map>

class SFXAudioManager : public AudioManager {
public:
    void playSound(const std::string& soundName, float volume) override;
private:
    std::map<std::string, sf::SoundBuffer> buffers;
    std::vector<sf::Sound> activeSounds;
};