//
//  AssetManager.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 20/07/25.
//

#include "AssetManager.hpp"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::getInstance(SDL_Renderer* renderer = nullptr) {
    if (!instance) {
        instance = new AssetManager(renderer);
    }
    return instance;
}

AssetManager::AssetManager(SDL_Renderer* renderer): renderer(renderer) {}

//Checa para ver se ja existe uma textura inicializada com o nome, se sim apenas retorna ela
SDL_Texture* AssetManager::getAsset(const std::string& assetName){
    for (size_t i = 0; i < assetNames.size(); ++i) {
        if (assetNames[i] == assetName) {
            return textureNames[i];
        }
    }
    
    SDL_Surface* sprite = IMG_Load(assetName.c_str());
    
    if (!sprite) {
        std::cerr << "Error loading surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* shapeTexture = SDL_CreateTextureFromSurface(renderer, sprite);
    SDL_FreeSurface(sprite);

    if (!shapeTexture) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    assetNames.push_back(assetName);
    textureNames.push_back(shapeTexture);

    return shapeTexture;

}

AssetManager::~AssetManager() {
    for (SDL_Texture* texture : textureNames) {
        SDL_DestroyTexture(texture);
    }
}
