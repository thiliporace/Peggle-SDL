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
#include "Label.hpp"

//60 FPS
//const float MS_PER_UPDATE = 0.016;
//240 FPS
const float MS_PER_UPDATE = 0.004;

int lives = 3;
int score = 0;
bool isGameOver = false;

std::shared_ptr<BallGameObject> ball;

std::shared_ptr<Label> livesLabel;
std::shared_ptr<Label> scoreLabel;
std::shared_ptr<Label> gameOverLabel;

//Armazena todos os objetos na cena pra atualizar todos de uma vez
std::list<std::shared_ptr<GameObject>> gameObjectsInScene; //Ponteiros inteligentes pra evitar problemas com gerenciamento de memória

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void update(float deltaTime){
    for (auto& gameObject : gameObjectsInScene){
        gameObject->update(deltaTime);
    }
    
    if (ball->didFall()) {
        lives--;
        livesLabel->setValue(lives);
        
        if (lives > 0) {
            ball->reset();
        } else {
            isGameOver = true;
            gameOverLabel = std::make_shared<Label>(250, 250, -1, "GAME OVER");
        }
    }
}

void render(SDL_Renderer* renderer, std::shared_ptr<BallGameObject> ball){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    ball->renderTrajectory(renderer);
    
    for(auto& gameObject : gameObjectsInScene){
        if (!gameObject->getIsAlive() || !gameObject->getTexture()) continue;
                
        SDL_RenderCopyExF(renderer, gameObject->getTexture(), NULL, &gameObject->renderRect, gameObject->rotation, NULL, SDL_FLIP_NONE);
    }
    
    if (livesLabel && livesLabel->getTexture()) {
        SDL_Rect rect = livesLabel->getRect();
        SDL_RenderCopy(renderer, livesLabel->getTexture(), NULL, &rect);
    }
    if (scoreLabel && scoreLabel->getTexture()) {
        SDL_Rect rect = scoreLabel->getRect();
        SDL_RenderCopy(renderer, scoreLabel->getTexture(), NULL, &rect);
    }
    if (isGameOver && gameOverLabel && gameOverLabel->getTexture()){
        SDL_Rect rect = gameOverLabel->getRect();
        SDL_RenderCopy(renderer, gameOverLabel->getTexture(), NULL, &rect);
    }
    
    SDL_RenderPresent(renderer);
}

int main(){
    //Singleton pra funções comuns do SDL
    SdlManager* sdlManager = SdlManager::getInstance();
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    CollisionDetection collisionDetection = CollisionDetection();
    
    ball = std::make_shared<BallGameObject>(400, 50, 10, "ball.png");
    
    livesLabel = std::make_shared<Label>(10, 10, lives, "Vidas: ");
    scoreLabel = std::make_shared<Label>(650, 10, score, "Pontos: ");
    
    gameObjectsInScene.push_back(ball);

    int y_coords[] = {300, 500};

    for (int y : y_coords) {
        for (int x = 100; x <= 700; x += 100) {
            std::shared_ptr<PeggleGameObject> peggle = std::make_shared<PeggleGameObject>(BASIC, *ball, x, y, 10, "whitePin.png");
            peggle->AddDelegate([&collisionDetection](const CircleCollider& colliderA, const CircleCollider& colliderB){
                return collisionDetection.checkCircleCollision(colliderA, colliderB);
            });
            peggle->setScoringDelegate([&]() {
                score += 20;
                scoreLabel->setValue(score);
            });
            gameObjectsInScene.push_back(peggle);
        }
    }
        
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    
    double lag = 0.0;
    double fpsCounter = 0.0;
    
    int frames = 0;
    
    while (!quit){
        
        if(isGameOver) quit = true;
           
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
               case SDL_MOUSEMOTION:
                   if (ball->getState() == AIMING) {
                       ball->setAimDirection(event.motion.x, event.motion.y);
                   }
                   break;
               
               case SDL_MOUSEBUTTONDOWN:
                   if (event.button.button == SDL_BUTTON_LEFT && ball->getState() == AIMING) {
                       ball->launch();
                   }
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
       
       render(renderer,ball);
   }
    
    return 0;
}
