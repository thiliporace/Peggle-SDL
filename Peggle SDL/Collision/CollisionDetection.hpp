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

class CollisionDetection{
public:
    bool checkCollision(SDL_FRect rectA, SDL_FRect rectB);
};

#endif /* CollisionDetection_hpp */
