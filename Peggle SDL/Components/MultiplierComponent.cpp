//
//  MultiplierComponent.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#include "MultiplierComponent.hpp"

MultiplierComponent::MultiplierComponent(OnHitMultiplyScoreDelegate handler) : multiplyDelegate(handler) {}

void MultiplierComponent::onHit(PeggleGameObject* peggle) {
    if (multiplyDelegate) {
        multiplyDelegate();
    }
}
