//
//  BallGameObject.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#include "BallGameObject.hpp"

#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float GRAVITY = 980.0f;

const int TRAJECTORY_SIM_STEPS = 60;
const float TRAJECTORY_TIME_STEP = 0.016f;

BallGameObject::BallGameObject(float initialX, float initialY, float radius, const std::string& assetName, double rotation): GameObject(initialX, initialY, radius, assetName, rotation) {
    currentState = AIMING;
    velX = 0;
    velY = 0;
    
    this->initialX = initialX;
    this->initialY = initialY;
    
    aimDirX = 0.0f;
    aimDirY = 1.0f;
    
    hasFallen = false;
}

void BallGameObject::update(float deltaTime){
    if (currentState == LAUNCHED) {
        velY += GRAVITY * deltaTime;
            
        collider.x += velX * deltaTime;
        collider.y += velY * deltaTime;
        
        if (collider.x - collider.radius < 0) {
            collider.x = collider.radius;
            velX *= -1;
        }
        
        if (collider.x + collider.radius > SCREEN_WIDTH) {
            collider.x = SCREEN_WIDTH - collider.radius;
            velX *= -1;
        }
        
        if (collider.y + collider.radius > 600) {
            hasFallen = true;
        }
        
        renderRect.x = collider.x - collider.radius;
        renderRect.y = collider.y - collider.radius;
    }
}

void BallGameObject::setAimDirection(int mouseX, int mouseY) {
    if (mouseY <= collider.y) {
        return;
    }

    float dirX = mouseX - collider.x;
    float dirY = mouseY - collider.y;
    
    float length = std::sqrt(dirX * dirX + dirY * dirY);
    
    if (length > 0) {
        aimDirX = dirX / length;
        aimDirY = dirY / length;
    }
}

void BallGameObject::launch() {
    if (currentState == AIMING) {
        currentState = LAUNCHED;
        
        velX = aimDirX * LAUNCH_SPEED;
        velY = aimDirY * LAUNCH_SPEED;
    }
}

void BallGameObject::renderTrajectory(SDL_Renderer* renderer) {
    if (currentState == AIMING) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        float simX = collider.x;
        float simY = collider.y;
        float simVelX = aimDirX * LAUNCH_SPEED;
        float simVelY = aimDirY * LAUNCH_SPEED;
        
        for (int i = 0; i < TRAJECTORY_SIM_STEPS; ++i) {
            
            simVelY += GRAVITY * TRAJECTORY_TIME_STEP;
            simX += simVelX * TRAJECTORY_TIME_STEP;
            simY += simVelY * TRAJECTORY_TIME_STEP;
            
            if (i % 4 == 0) {
                SDL_RenderDrawPointF(renderer, simX, simY);
            }
        }
    }
}

BallState BallGameObject::getState() const {
    return currentState;
}

void BallGameObject::rebound(const CircleCollider& otherCollider){
    //Monta vetor da bola até o pino
    float normalX = collider.x - otherCollider.x;
    float normalY = collider.y - otherCollider.y;
    
    //Pega a magnitude do vetor e depois normaliza ele
    float length = std::sqrt(normalX * normalX + normalY * normalY);
    if (length == 0.0f) {
        length = 1.0f; 
        normalX = 1.0f;
        normalY = 0.0f;
    } else {
        normalX /= length;
        normalY /= length;
    }
    
    //Pega o vetor da velocidade da bola e faz o produto escalar com o vetor até o pino encontrado, pegando a projecao da velocidade em direcao ao pino
    float dotProduct = velX * normalX + velY * normalY;
    
    //Aplica a formula de reflexao de vetores
    velX = velX - 2 * dotProduct * normalX;
    velY = velY - 2 * dotProduct * normalY;
}

void BallGameObject::reset() {
    currentState = AIMING;
    
    collider.x = initialX;
    collider.y = initialY;
    
    velX = 0;
    velY = 0;
    
    renderRect.x = collider.x - collider.radius;
    renderRect.y = collider.y - collider.radius;
    
    hasFallen = false;
}

bool BallGameObject::didFall() const {
    return hasFallen;
}
