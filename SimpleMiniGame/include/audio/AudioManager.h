#pragma once
#include <string>

class AudioManager {
public:
    virtual ~AudioManager() = default;
    virtual void playSound(const std::string& soundName, float volume) = 0;
};