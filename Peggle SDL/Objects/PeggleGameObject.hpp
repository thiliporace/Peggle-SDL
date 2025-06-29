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

class PeggleGameObject: public GameObject{
private:
    PeggleType peggleType;
    BallGameObject& ballGameObject;
    
    OnCollisionDetectionDelegate delegate;
    
    OnHitScoringDelegate scoringDelegate;
public:
    PeggleGameObject(PeggleType type, BallGameObject& ballGameObject, float initialX, float initialY, float radius, const std::string& assetName, double rotation = 0);
    
    void update(float deltaTime) override;
    
    void changePeggleType(const PeggleType& newType, const std::string& newAssetName);
    
    void AddDelegate(OnCollisionDetectionDelegate handler);
    
    void setScoringDelegate(OnHitScoringDelegate handler);
};

#endif /* PeggleGameObject_hpp */
