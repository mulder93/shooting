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

    m_worldBounds = cocos2d::Rect({0.0f, 0.0f}, cocos2d::Director::getInstance()->getVisibleSize());

    scheduleUpdate();

    return true;
}

void PhysicsBody::update(float delta)
{
    setPosition(getPosition() + getVelocity() * delta);
    setVelocity(getVelocity() + getAcceleration() * delta);
}
