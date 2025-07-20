//
//  PeggleGameObject.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#include "PeggleGameObject.hpp"

PeggleGameObject::PeggleGameObject(PeggleType type, std::list<std::shared_ptr<GameObject>>& gameObjects, float initialX, float initialY, float radius, const std::string& assetName, AudioManager& audioManager, double rotation): GameObject(initialX, initialY, radius, assetName, audioManager, rotation), peggleType(type), gameObjectsInScene(gameObjects){
    changePeggleType(type, type == BASIC ? "whitePin.png" : type == BONUS ? "yellowPin.png" : "bluePin.png");
}

void PeggleGameObject::update(float deltaTime){
    if (!isAlive) return;
    
    for (auto& gameObject : gameObjectsInScene) {
        BallGameObject* ball = dynamic_cast<BallGameObject*>(gameObject.get());

        if (ball && ball->getState() != AIMING) {
            if (collisionDetectionDelegate && collisionDetectionDelegate(this->collider, ball->collider)) {
                setIsAlive(false);
                audioManager.queueSound("peghit");
                
                switch (peggleType){
                    case BASIC:
                        if (!scoringDelegate) break;
                        scoringDelegate();
                        break;
                    case BONUS:
                        scoringDelegate();
                        multiplyDelegate();
                        break;
                    case SPAWNBALL:
                        spawnBallDelegate();
                        break;
                    default:
                        break;
                }

                ball->rebound(this->collider);

                break;
            }
        }
    }
}

void PeggleGameObject::changePeggleType(const PeggleType& newType, const std::string& newAssetName){
    peggleType = newType;
    changeAsset(newAssetName);
}

void PeggleGameObject::AddDelegate(OnCollisionDetectionDelegate handler){
    if (collisionDetectionDelegate != nullptr) return;
    collisionDetectionDelegate = handler;
}

void PeggleGameObject::setScoringDelegate(OnHitScoringDelegate handler) {
    if (scoringDelegate != nullptr) return;
    scoringDelegate = handler;
}

void PeggleGameObject::setMultiplyScoreDelegate(OnHitMultiplyScoreDelegate handler) {
    if (multiplyDelegate != nullptr) return;
    multiplyDelegate = handler;
}

void PeggleGameObject::setSpawnBallDelegate(OnHitSpawnBallDelegate handler) {
    if (spawnBallDelegate != nullptr) return;
    spawnBallDelegate = handler;
}
