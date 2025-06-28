//
//  CollisionDetection.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 13/05/25.
//

#ifndef CollisionDetection_hpp
#define CollisionDetection_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

#include "CircleCollider.h"

class CollisionDetection{
public:
    bool checkCollision(const SDL_FRect rectA, const SDL_FRect rectB);
    
    bool checkCircleCollision(const CircleCollider& a, const CircleCollider& b);
};

#endif /* CollisionDetection_hpp */
