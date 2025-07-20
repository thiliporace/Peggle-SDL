//
//  AudioManager.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 20/07/25.
//

#include "AudioManager.hpp"

AudioManager::AudioManager() {
    init();
    loadSound("extremefever", "extremefever.mp3");
    loadSound("aah", "aah.mp3");
    loadSound("applause", "applause.mp3");
    loadSound("ball_add", "ball_add.mp3");
    loadSound("cannonshot", "cannonshot.mp3");
    loadSound("extraball", "extraball.mp3");
    loadSound("peghit", "peghit.mp3");
    loadSound("powerupluckyspin", "powerup_luckyspin.mp3");
    loadSound("powerupspooky", "powerup_spooky2.mp3");
    loadSound("powerupzen", "powerup_zen3.mp3");
    loadSound("scorecounter", "scorecounter.mp3");
}

AudioManager::~AudioManager() {
    for (auto const& [id, sound] : soundMap) {
        Mix_FreeChunk(sound);
    }

    soundMap.clear();

    // Fecha o SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();
}

bool AudioManager::init() {
    // Inicializa o SDL_mixer
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        std::cout << "Falha ao inicializar o SDL_mixer com suporte a MP3: " << Mix_GetError() << std::endl;
        return false;
    }

    // Abre o dispositivo de áudio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cout << "Falha ao abrir o áudio: " << Mix_GetError() << std::endl;
        return false;
    }
    
    Mix_AllocateChannels(32);
    
    return true;
}

bool AudioManager::loadSound(const std::string& id, const std::string& path) {
    // A função chama se Mix_LoadWAV mas carrega varios formatos
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        std::cerr << "Falha ao carregar o som '" << path << "': " << Mix_GetError() << std::endl;
        return false;
    }
    soundMap[id] = sound;
    return true;
}

void AudioManager::playSound(const std::string& id) {
    if (soundMap.find(id) != soundMap.end()) {
        if (Mix_PlayChannel(-1, soundMap[id], 0) == -1) {
            std::cerr << "Falha ao tocar o som '" << id << "': " << Mix_GetError() << std::endl;
        }
    }
}
