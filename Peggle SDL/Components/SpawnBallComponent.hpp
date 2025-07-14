//
//  SpawnBallComponent.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#ifndef SpawnBallComponent_hpp
#define SpawnBallComponent_hpp

#include <stdio.h>
#include <functional>

#include "OnHitComponent.h"

using OnHitSpawnBallDelegate = std::function<void()>;

class SpawnBallComponent : public OnHitComponent {
public:
    SpawnBallComponent(OnHitSpawnBallDelegate handler);
    virtual void onHit(PeggleGameObject* peggle) override;

private:
    OnHitSpawnBallDelegate spawnBallDelegate;
};

#endif /* SpawnBallComponent_hpp */
