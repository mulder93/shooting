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
    CollisionDetector() = default;

    CollisionDetector(const CollisionDetector&) = delete;
    CollisionDetector& operator=(const CollisionDetector&) = delete;
    
    CollisionDetector(CollisionDetector&&) = default;
    CollisionDetector& operator=(CollisionDetector&&) = default;

    void registerBody(PhysicsBody* body);
    void update(float delta);

private:
    cocos2d::Vector<PhysicsBody*> m_bodies;
};
