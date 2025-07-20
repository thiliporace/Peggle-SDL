//
//  AssetManager.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 20/07/25.
//

#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <stdio.h>
#include <iostream>
#include <list>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

class AssetManager {
private:
    //Precisamos receber o renderer para criar a textura da forma
    SDL_Renderer* renderer;
    //Vetor com referencia as texturas ja criadas
    std::vector <SDL_Texture*> textureNames;
    //Vetor com os nomes ja usados para texturas
    std::vector <std::string> assetNames;
    
    //Instancia unica da classe singleton
    static AssetManager* instance;
    
    AssetManager(const AssetManager& obj) = delete;
    
    AssetManager(SDL_Renderer* renderer);
public:
    static AssetManager* getInstance(SDL_Renderer* renderer);
    
    SDL_Texture* getAsset(const std::string& assetName);
    
    ~AssetManager();
};

#endif /* AssetManager_hpp */
