#pragma once
#include "AudioManager.h"

class NullAudioManager : public AudioManager {
public:
    void playSound(const std::string&, float) override {}
};
