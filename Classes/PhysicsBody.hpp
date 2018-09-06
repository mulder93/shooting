//
//  PhysicsBody.hpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#pragma once

#include "cocos2d.h"
#include <iostream>

class PhysicsBody : public cocos2d::Node
{
public:
    bool init() override;

    void update(float delta) override;

    const cocos2d::Vec2& getVelocity() { return m_velocity; }
    void setVelocity(cocos2d::Vec2 velocity) { m_velocity = std::move(velocity); }

    virtual cocos2d::Rect getCollisionBox() const = 0;

    virtual void onCollide(PhysicsBody* collideBody) {}

private:
    cocos2d::Vec2 m_velocity{0.0f, 0.0f};
};
