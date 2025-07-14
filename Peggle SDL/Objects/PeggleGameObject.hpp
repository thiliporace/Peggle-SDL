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
#include "OnHitComponent.h"

using OnCollisionDetectionDelegate = std::function<bool(const CircleCollider& colliderA, const CircleCollider& colliderB)>;

class PeggleGameObject: public GameObject {
private:
    std::list<std::shared_ptr<GameObject>>& gameObjectsInScene;
    OnCollisionDetectionDelegate collisionDetectionDelegate;
    std::vector<std::shared_ptr<OnHitComponent>> onHitComponents;

public:
    PeggleGameObject(std::list<std::shared_ptr<GameObject>>& gameObjects, float initialX, float initialY, float radius, const std::string& assetName, double rotation = 0);
    
    void update(float deltaTime) override;
    
    void addOnHitComponent(std::shared_ptr<OnHitComponent> component);
    void setCollisionDelegate(OnCollisionDetectionDelegate handler);
};

#endif /* PeggleGameObject_hpp */
