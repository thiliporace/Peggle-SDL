//
//  AudioManager.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 20/07/25.
//

#ifndef AudioManager_hpp
#define AudioManager_hpp

#include <iostream>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include <map>

// Estrutura para representar um pedido de som pendente
struct SoundRequest {
    std::string id;
};

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool init();
    
    void queueSound(const std::string& id);

    bool loadSound(const std::string& id, const std::string& path);
    
    void update();

private:
    static const int MAX_PENDING_SOUNDS = 32;
    
    SoundRequest pendingSounds[MAX_PENDING_SOUNDS];
    
    int head, tail;
    
    std::map<std::string, Mix_Chunk*> soundMap;
};

#endif /* AudioManager_hpp */
