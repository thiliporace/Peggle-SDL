//
//  PeggleGameObject.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#ifndef PeggleGameObject_hpp
#define PeggleGameObject_hpp

#include <stdio.h>

#include "GameObject.hpp"
#include "BallGameObject.hpp"
#include "PeggleType.h"
#include "CollisionDetection.hpp"

//Delegate pra funçao do Collision Detection
using OnCollisionDetectionDelegate = std::function<bool(const CircleCollider& colliderA, const CircleCollider& colliderB)>;

using OnHitScoringDelegate = std::function<void()>;

using OnHitMultiplyScoreDelegate = std::function<void()>;

using OnHitSpawnBallDelegate = std::function<void()>;

class PeggleGameObject: public GameObject{
private:
    PeggleType peggleType;
    
    std::list<std::shared_ptr<GameObject>>& gameObjectsInScene;
    
    OnCollisionDetectionDelegate collisionDetectionDelegate;
    
    OnHitScoringDelegate scoringDelegate;
    OnHitMultiplyScoreDelegate multiplyDelegate;
    OnHitSpawnBallDelegate spawnBallDelegate;
    
public:
    PeggleGameObject(PeggleType type, std::list<std::shared_ptr<GameObject>>& gameObjects, float initialX, float initialY, float radius, const std::string& assetName, double rotation = 0);
    
    void update(float deltaTime) override;
    
    void changePeggleType(const PeggleType& newType, const std::string& newAssetName);
    
    void AddDelegate(OnCollisionDetectionDelegate handler);
    
    void setScoringDelegate(OnHitScoringDelegate handler);
    void setMultiplyScoreDelegate(OnHitMultiplyScoreDelegate handler);
    void setSpawnBallDelegate(OnHitSpawnBallDelegate handler);
};

#endif /* PeggleGameObject_hpp */
