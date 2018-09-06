//
//  PhysicsBody.cpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "PhysicsBody.hpp"

bool PhysicsBody::init()
{
    if (!Node::init())
        return false;

    scheduleUpdate();

    return true;
}

void PhysicsBody::update(float delta)
{
    setPosition(getPosition() + getVelocity() * delta);
}
