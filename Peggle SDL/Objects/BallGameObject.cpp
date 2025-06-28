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

BallGameObject::BallGameObject(float initialX, float initialY, float radius, const std::string& assetName, double rotation): GameObject(initialX, initialY, radius, assetName, rotation) {}

void BallGameObject::update(float deltaTime){
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
        collider.y = 600 - collider.radius;
        velY *= -1;
    }
    
    renderRect.x = collider.x - collider.radius;
    renderRect.y = collider.y - collider.radius;
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
