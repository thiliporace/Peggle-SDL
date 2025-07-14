//
//  MultiplierComponent.hpp
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#ifndef MultiplierComponent_hpp
#define MultiplierComponent_hpp

#include <stdio.h>
#include <functional>

#include "OnHitComponent.h"

using OnHitMultiplyScoreDelegate = std::function<void()>;

class MultiplierComponent : public OnHitComponent {
public:
    MultiplierComponent(OnHitMultiplyScoreDelegate handler);
    virtual void onHit(PeggleGameObject* peggle) override;

private:
    OnHitMultiplyScoreDelegate multiplyDelegate;
};

#endif /* MultiplierComponent_hpp */
