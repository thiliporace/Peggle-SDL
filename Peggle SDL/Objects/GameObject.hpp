//
//  GameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <string.h>
#include <stdio.h>
#include <list>
#include <SDL2/SDL.h>

#include "CircleCollider.h"
#include "AudioManager.hpp"

class GameObject {
private:
    SDL_Surface* sprite;
    
    SDL_Texture* spriteTexture;
    
    float width,height;

protected:
    bool isAlive;
    
    AudioManager& audioManager;
    
public:
    CircleCollider collider;
    
    SDL_FRect renderRect;
    
    double rotation;
    
    GameObject(float initialX, float initialY, float radius, const std::string& assetName, AudioManager& audioManager, double rotation = 0);
    
    void changeAsset(const std::string& assetName);
    
    virtual void update(float deltaTime) = 0;
    
    SDL_Texture* getTexture();
    
    bool getIsAlive();
    
    void setIsAlive(bool b);
    
    virtual ~GameObject();
};

#endif /* GameObject_hpp */
