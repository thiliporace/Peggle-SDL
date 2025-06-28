//
//  CollisionDetection.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 13/05/25.
//

#include "CollisionDetection.hpp"

bool CollisionDetection::checkCollision(const SDL_FRect rectA, const SDL_FRect rectB){
    int topA,topB,bottomA,bottomB,rightA,rightB,leftA,leftB;
    
    leftA = rectA.x;
    rightA = leftA + rectA.w;
    topA = rectA.y;
    bottomA = topA + rectA.h;
    
    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = topB + rectB.h;
    
    if(bottomA <= bottomB) return false;
    
    if(topA >= bottomB) return false;
    
    if(rightA <= leftB) return false;
    
    if(leftA >= rightB) return false;
    
    return true;
}

bool CollisionDetection::checkCircleCollision(const CircleCollider& a, const CircleCollider& b){
    float distanceX = a.x - b.x;
    float distanceY = a.y - b.y;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    float radiiSum = a.radius + b.radius;
    
    float radiiSumSquared = radiiSum * radiiSum;

    return distanceSquared <= radiiSumSquared;
}
