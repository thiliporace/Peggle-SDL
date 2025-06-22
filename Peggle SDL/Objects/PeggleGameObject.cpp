//
//  PeggleGameObject.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#include "PeggleGameObject.hpp"

PeggleGameObject::PeggleGameObject(PeggleType type, BallGameObject& ballGameObject, float initialX, float initialY, float radius, const std::string& assetName, double rotation): GameObject(initialX, initialY, radius, assetName, rotation), peggleType(type), ballGameObject(ballGameObject){
    collisionDetection = CollisionDetection();
}

void PeggleGameObject::update(float deltaTime){
    float distanceX = ballGameObject.collider.x - this->collider.x;
    float distanceY = ballGameObject.collider.y - this->collider.y;
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    float radiiSum = ballGameObject.collider.radius + this->collider.radius;
    float radiiSumSquared = radiiSum * radiiSum;

    if (distanceSquared <= radiiSumSquared) {
        ballGameObject.rebound(this->collider);
        
        if (peggleType == INACTIVE) return;
        
        changePeggleType(INACTIVE, "grayPin.png");
    }

    renderRect.x = collider.x - collider.radius;
    renderRect.y = collider.y - collider.radius;
}

void PeggleGameObject::changePeggleType(const PeggleType& newType, const std::string& newAssetName){
    peggleType = newType;
    changeAsset(newAssetName);
}
