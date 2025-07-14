//
//  ScoringComponent.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#ifndef ScoringComponent_hpp
#define ScoringComponent_hpp

#include <stdio.h>
#include <functional>
#include "OnHitComponent.h"

using OnHitScoringDelegate = std::function<void()>;

class ScoringComponent : public OnHitComponent {
public:
    ScoringComponent(OnHitScoringDelegate handler);
    virtual void onHit(PeggleGameObject* peggle) override;

private:
    OnHitScoringDelegate scoringDelegate;
};


#endif /* ScoringComponent_hpp */
