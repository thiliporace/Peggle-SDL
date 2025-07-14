#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <list>

#include "SdlManager.hpp"
#include "GameObject.hpp"
#include "BallGameObject.hpp"
#include "PeggleGameObject.hpp"
#include "Label.hpp"
#include "CollisionDetection.hpp"
#include "ScoringComponent.hpp"
#include "MultiplierComponent.hpp"
#include "SpawnBallComponent.hpp"

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

enum PeggleType { BASIC, BONUS, SPAWNBALL };

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void update(float deltaTime){
    for (auto& gameObject : gameObjectsInScene){
        gameObject->update(deltaTime);
    }
    
    if (ball->didFall()) {
        if (!isGameOver) lives--;
        livesLabel->setValue(lives);
        
        if (lives > 0) {
            ball->reset();
        } else {
            isGameOver = true;
            gameOverLabel = std::make_shared<Label>(400, 250, -1, "GAME OVER");
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
    
    SDL_RenderPresent(renderer);
}

int main(){
    //Singleton pra funções comuns do SDL
    SdlManager* sdlManager = SdlManager::getInstance();
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    CollisionDetection collisionDetection = CollisionDetection();
    
    ball = std::make_shared<BallGameObject>(400, 50, 10, "ball.png");
    
    livesLabel = std::make_shared<Label>(10, 10, lives, "Lives: ");
    scoreLabel = std::make_shared<Label>(650, 10, score, "Points: ");
    
    gameObjectsInScene.push_back(ball);

    const int centerX = 400;
    const int startY = 200;
    const int horizontalSpacing = 60;
    const int verticalSpacing = 50;

    int pegsPerRow[] = {1, 3, 5, 7, 7, 5, 3, 1};
    int numRows = sizeof(pegsPerRow) / sizeof(pegsPerRow[0]);

    auto collisionHandler = [&collisionDetection](const CircleCollider& colliderA, const CircleCollider& colliderB){
        return collisionDetection.checkCircleCollision(colliderA, colliderB);
    };

    auto scoringHandler = [&]() {
        score += 20;
        scoreLabel->setValue(score);
    };

    auto multiplyHandler = [&]() {
        score *= 1.2;
        scoreLabel->setValue(score);
    };

    auto spawnBallHandler = [&]() {
        std::shared_ptr<BallGameObject> newBall = std::make_shared<BallGameObject>(400, 50, 10, "ball.png");
        gameObjectsInScene.push_back(newBall);
        newBall->setAimDirection(rand() % 800, rand() % 800);
        newBall->launch();
    };

    for (int i = 0; i < numRows; ++i) {
        int numPegs = pegsPerRow[i];
        float rowWidth = (numPegs - 1) * horizontalSpacing;
        float startX = centerX - (rowWidth / 2.0f);
        int y = startY + i * verticalSpacing;

        for (int j = 0; j < numPegs; ++j) {
            int x = startX + j * horizontalSpacing;

            PeggleType type = static_cast<PeggleType>(rand() % 3);
            std::shared_ptr<PeggleGameObject> peggle;

            // std::shared_ptr<PeggleGameObject> peggle = std::make_shared<PeggleGameObject>(SPAWNBALL, gameObjectsInScene, x, y, 10, "whitePin.png");

            switch (type) {
                case BONUS:
                    peggle = std::make_shared<PeggleGameObject>(gameObjectsInScene, x, y, 10, "yellowPin.png");
                    peggle->addOnHitComponent(std::make_shared<ScoringComponent>(scoringHandler));
                    peggle->addOnHitComponent(std::make_shared<MultiplierComponent>(multiplyHandler));
                    break;
                case SPAWNBALL:
                    peggle = std::make_shared<PeggleGameObject>(gameObjectsInScene, x, y, 10, "bluePin.png");
                    peggle->addOnHitComponent(std::make_shared<SpawnBallComponent>(spawnBallHandler));
                    break;
                case BASIC:
                default:
                    peggle = std::make_shared<PeggleGameObject>(gameObjectsInScene, x, y, 10, "whitePin.png");
                    peggle->addOnHitComponent(std::make_shared<ScoringComponent>(scoringHandler));
                    break;
            }
            
            peggle->setCollisionDelegate(collisionHandler);
            gameObjectsInScene.push_back(peggle);
        }
    }
        
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    
    double lag = 0.0;
    double fpsCounter = 0.0;
    
    int renderFrames = 0;
    int updateFrames = 0;
    
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
            updateFrames++;
            update(MS_PER_UPDATE);
            lag -= MS_PER_UPDATE;
        }
        
        if (fpsCounter >= 1.0f){
            std::cout << "UPDATE FPS: " << updateFrames << std::endl;
            std::cout << "RENDER FPS: " << renderFrames << std::endl;
            
            updateFrames = 0;
            renderFrames = 0;
            fpsCounter -= 1.0f;
        }
        
        render(renderer,ball);
        renderFrames++;
    }
    
    return 0;
}
