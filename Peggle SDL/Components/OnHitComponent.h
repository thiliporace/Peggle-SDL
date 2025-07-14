//
//  OnHitComponent.h
//  Peggle SDL
//
//  Created by Thiago Liporace on 13/07/25.
//

#ifndef OnHitComponent_h
#define OnHitComponent_h

class PeggleGameObject;

class OnHitComponent {
public:
    virtual ~OnHitComponent() {}
    virtual void onHit(PeggleGameObject* peggle) = 0;
};

#endif /* OnHitComponent_h */
