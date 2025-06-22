//
//  main.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <list>

#include "SdlManager.hpp"
#include "GameObject.hpp"
#include "BallGameObject.hpp"
#include "PeggleGameObject.hpp"

//60 FPS
//const float MS_PER_UPDATE = 0.016;
//240 FPS
const float MS_PER_UPDATE = 0.004;

//Armazena todos os objetos na cena pra atualizar todos de uma vez
std::list<std::shared_ptr<GameObject>> gameObjectsInScene; //Ponteiros inteligentes pra evitar problemas com gerenciamento de memória

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void update(float deltaTime){
    for (auto& gameObject : gameObjectsInScene){
        gameObject->update(deltaTime);
    }
}

void render(SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    
    for(auto& gameObject : gameObjectsInScene){
        if (!gameObject->getIsAlive() || !gameObject->getTexture()) continue;
                
        SDL_RenderCopyExF(renderer, gameObject->getTexture(), NULL, &gameObject->renderRect, gameObject->rotation, NULL, SDL_FLIP_NONE);
    }
    
    SDL_RenderPresent(renderer);
}

int main(){
    //Singleton pra funções comuns do SDL
    SdlManager* sdlManager = SdlManager::getInstance();
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    std::shared_ptr<BallGameObject> ball = std::make_shared<BallGameObject>(410, 100, 10, "ball.png");
    
    std::shared_ptr<PeggleGameObject> peggle1 = std::make_shared<PeggleGameObject>(BASIC, *ball, 100, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle2 = std::make_shared<PeggleGameObject>(BASIC, *ball, 200, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle3 = std::make_shared<PeggleGameObject>(BASIC, *ball, 300, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle4 = std::make_shared<PeggleGameObject>(BASIC, *ball, 400, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle5 = std::make_shared<PeggleGameObject>(BASIC, *ball, 500, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle6 = std::make_shared<PeggleGameObject>(BASIC, *ball, 600, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle7 = std::make_shared<PeggleGameObject>(BASIC, *ball, 700, 300, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle8 = std::make_shared<PeggleGameObject>(BASIC, *ball, 100, 500, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle9 = std::make_shared<PeggleGameObject>(BASIC, *ball, 200, 500, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle10 = std::make_shared<PeggleGameObject>(BASIC, *ball, 300, 500, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle11 = std::make_shared<PeggleGameObject>(BASIC, *ball, 400, 500, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle12 = std::make_shared<PeggleGameObject>(BASIC, *ball, 500, 500, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle13 = std::make_shared<PeggleGameObject>(BASIC, *ball, 600, 500, 10, "whitePin.png");
    std::shared_ptr<PeggleGameObject> peggle14 = std::make_shared<PeggleGameObject>(BASIC, *ball, 700, 500, 10, "whitePin.png");
    
    gameObjectsInScene.push_back(ball);
    gameObjectsInScene.push_back(peggle1);
    gameObjectsInScene.push_back(peggle2);
    gameObjectsInScene.push_back(peggle3);
    gameObjectsInScene.push_back(peggle4);
    gameObjectsInScene.push_back(peggle5);
    gameObjectsInScene.push_back(peggle6);
    gameObjectsInScene.push_back(peggle7);
    gameObjectsInScene.push_back(peggle8);
    gameObjectsInScene.push_back(peggle9);
    gameObjectsInScene.push_back(peggle10);
    gameObjectsInScene.push_back(peggle11);
    gameObjectsInScene.push_back(peggle12);
    gameObjectsInScene.push_back(peggle13);
    gameObjectsInScene.push_back(peggle14);
        
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    
    double lag = 0.0;
    double fpsCounter = 0.0;
    
    int frames = 0;
    
    while (!quit){
           
       double current = getCurrentTime();
       double elapsed = current - previous;
       previous = current;
       lag += elapsed;
       fpsCounter += elapsed;
       
       while(SDL_PollEvent(&event)){
           switch(event.type){
               case SDL_QUIT:
                   quit = true;
                   break;
           }
           
       }
       
       //Usando o Game Programming Pattern Update pra manter uma taxa de frames fixa, com um time step fixo e uma renderização variável (como não passamos lag residual pra renderização, em máquinas mais lentas a renderização pode ocorrer menos frequentemente que o update, causando artefatos visuais. Como essa máquina é meio goat 🐐 (bode 🐐) a renderização sempre roda mais rápido (uns 1000fps enquanto o update roda a uma taxa fixa))
       while (lag >= MS_PER_UPDATE){
           frames++;
           update(MS_PER_UPDATE);
           lag -= MS_PER_UPDATE;
       }
       
       if (fpsCounter >= 1.0f){
           fpsCounter = 0;
           std::cout << "FPS: " << frames << std::endl;
           frames = 0;
       }
       
       render(renderer);
   }
    
    return 0;
}
