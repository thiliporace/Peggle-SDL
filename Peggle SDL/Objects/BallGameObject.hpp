//
//  BallGameObject.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#ifndef BallGameObject_hpp
#define BallGameObject_hpp

#include <stdio.h>
#include "GameObject.hpp"

class BallGameObject: public GameObject{
public:
    float velX = 0;
    float velY = 0;
    
    BallGameObject(float initialX, float initialY, float radius, const std::string& assetName, double rotation = 0);
    
    void update(float deltaTime) override;
    
    void rebound(const CircleCollider& otherCollider);
};

#endif /* BallGameObject_hpp */
