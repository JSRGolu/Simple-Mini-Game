#include "../../include/audio/ServiceLocator.h"

// Define static members
AudioManager* ServiceLocator::audioManager = nullptr;
NullAudioManager ServiceLocator::nullAudioManager;