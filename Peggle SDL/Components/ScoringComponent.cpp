//
//  ScoringComponent.cpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#include "ScoringComponent.hpp"

ScoringComponent::ScoringComponent(OnHitScoringDelegate handler) : scoringDelegate(handler) {}

void ScoringComponent::onHit(PeggleGameObject* peggle) {
    if (scoringDelegate) {
        scoringDelegate();
    }
}
