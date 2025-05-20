#pragma once
#include "AudioManager.h"
#include "NullAudioManager.h"

class ServiceLocator {
public:
    static AudioManager* getAudioManager() {
        return audioManager ? audioManager : &nullAudioManager;
    }
    static void provide(AudioManager* service) {
        audioManager = service;
    }
private:
    static AudioManager* audioManager;
    static NullAudioManager nullAudioManager;
};