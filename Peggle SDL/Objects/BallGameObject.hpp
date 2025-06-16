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
    BallGameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const std::string& assetName, double rotation = 0);
    
    void update(float deltaTime) override;
};

#endif /* BallGameObject_hpp */
