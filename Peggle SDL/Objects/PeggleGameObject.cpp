//
//  PeggleGameObject.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#include "PeggleGameObject.hpp"

PeggleGameObject::PeggleGameObject(PeggleType type, BallGameObject& ballGameObject, float initialX, float initialY, float radius, const std::string& assetName, double rotation): GameObject(initialX, initialY, radius, assetName, rotation), peggleType(type), ballGameObject(ballGameObject){}

void PeggleGameObject::update(float deltaTime){
    if (delegate && delegate(ballGameObject.collider, this->collider)) {
        ballGameObject.rebound(this->collider);
        
        if (peggleType == INACTIVE) return;
        
        if (scoringDelegate) {
            scoringDelegate();
        }
        
        changePeggleType(INACTIVE, "grayPin.png");
    }

    renderRect.x = collider.x - collider.radius;
    renderRect.y = collider.y - collider.radius;
}

void PeggleGameObject::changePeggleType(const PeggleType& newType, const std::string& newAssetName){
    peggleType = newType;
    changeAsset(newAssetName);
}

void PeggleGameObject::AddDelegate(OnCollisionDetectionDelegate handler){
    if (delegate != nullptr) return;
    delegate = handler;
}

void PeggleGameObject::setScoringDelegate(OnHitScoringDelegate handler) {
    scoringDelegate = handler;
}
