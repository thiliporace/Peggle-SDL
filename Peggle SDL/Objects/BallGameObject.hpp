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
#include "BallState.h"

class BallGameObject: public GameObject{
private:
    BallState currentState;
        
    float aimDirX = 0.0f;
    float aimDirY = 1.0f;
    
    float initialX, initialY;
    
    const float LAUNCH_SPEED = 800.0f; 
    const float TRAJECTORY_LENGTH = 300.0f;
    
    bool hasFallen;
public:
    float velX = 0;
    float velY = 0;
    
    BallGameObject(float initialX, float initialY, float radius, const std::string& assetName, AudioManager& audioManager, double rotation = 0);
    
    void update(float deltaTime) override;
    
    void rebound(const CircleCollider& otherCollider);
    
    void launch();
    void setAimDirection(int mouseX, int mouseY);
    void renderTrajectory(SDL_Renderer* renderer);
    
    void reset();
    
    bool didFall() const;
        
    BallState getState() const;
};

#endif /* BallGameObject_hpp */
