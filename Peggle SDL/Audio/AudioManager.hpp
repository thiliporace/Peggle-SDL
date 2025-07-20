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

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool init();

    bool loadSound(const std::string& id, const std::string& path);

    void playSound(const std::string& id);

private:
    std::map<std::string, Mix_Chunk*> soundMap;
};

#endif /* AudioManager_hpp */
