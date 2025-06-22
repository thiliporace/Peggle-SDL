//
//  CollisionDetection.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 13/05/25.
//

#include "CollisionDetection.hpp"

bool CollisionDetection::checkCollision(SDL_FRect rectA, SDL_FRect rectB){
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
