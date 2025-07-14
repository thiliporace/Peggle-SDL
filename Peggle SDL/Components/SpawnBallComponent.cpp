//
//  SpawnBallComponent.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#include "SpawnBallComponent.hpp"

SpawnBallComponent::SpawnBallComponent(OnHitSpawnBallDelegate handler) : spawnBallDelegate(handler) {}

void SpawnBallComponent::onHit(PeggleGameObject* peggle) {
    if (spawnBallDelegate) {
        spawnBallDelegate();
    }
}
