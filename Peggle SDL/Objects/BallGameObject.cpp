//
//  BallGameObject.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 16/06/25.
//

#include "BallGameObject.hpp"

BallGameObject::BallGameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const std::string& assetName, double rotation): GameObject(initialXPos, initialYPos, objectWidth, objectHeight, assetName, rotation) {}

void BallGameObject::update(float deltaTime){
    
}
