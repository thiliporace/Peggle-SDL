//
//  GameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "GameObject.hpp"
#include "SdlManager.hpp"
#include "AssetManager.hpp"

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

GameObject::GameObject(float initialX, float initialY, float radius, const std::string& assetName, double rotation) : isAlive(true), rotation(rotation) {
    
    SdlManager* sdlManager = SdlManager::getInstance();
    
    AssetManager* assetManager = AssetManager::getInstance(sdlManager->getRenderer());
    
    spriteTexture = assetManager->getAsset(assetName);
    
    SDL_FreeSurface(sprite);

    collider.x = initialX;
    collider.y = initialY;
    collider.radius = radius;
    
    renderRect.w = radius * 2;
    renderRect.h = radius * 2;
    renderRect.x = initialX - radius;
    renderRect.y = initialY - radius;
}

void GameObject::changeAsset(const std::string& assetName) {
    SdlManager* sdlManager = SdlManager::getInstance();

    SDL_Surface* newSprite = IMG_Load(assetName.c_str());

    if (!newSprite) {
        cout << "Error Surface: " << SDL_GetError() << endl;
        return;
    }

    if (spriteTexture) {
        SDL_DestroyTexture(spriteTexture);
    }

    spriteTexture = SDL_CreateTextureFromSurface(sdlManager->getRenderer(), newSprite);

    if (!spriteTexture) {
        cout << "Error Texture: " << SDL_GetError() << endl;
        return;
    }

    SDL_FreeSurface(newSprite);
}

GameObject::~GameObject(){
    if (spriteTexture) {
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = nullptr;
    }
}

SDL_Texture* GameObject::getTexture(){
    return spriteTexture;
}

bool GameObject::getIsAlive(){
    return isAlive;
}

void GameObject::setIsAlive(bool b){
    isAlive = b;
}
