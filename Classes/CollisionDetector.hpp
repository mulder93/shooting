//
//  CollisionDetector.hpp
//  shooting
//
//  Created by Boris Tsarev on 03/09/2018.
//

#pragma once

#include "cocos2d.h"
#include "PhysicsBody.hpp"

class CollisionDetector
{
public:
    void registerBody(PhysicsBody* body);
    void update(float delta);

private:
    cocos2d::Vector<PhysicsBody*> m_bodies;
};
