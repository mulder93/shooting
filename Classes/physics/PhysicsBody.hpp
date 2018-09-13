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

    const cocos2d::Vec2& getAcceleration() { return m_acceleration; }
    void setAcceleration(cocos2d::Vec2 acceleration) { m_acceleration = std::move(acceleration); }

    bool areCollisionsEnabled() const { return m_collisionsEnabled; }
    void setCollisionsEnabled(bool enabled) { m_collisionsEnabled = enabled; }

    virtual cocos2d::Rect getCollisionBox() const { return getBoundingBox(); }

    void setWorldBounds(cocos2d::Rect bounds) { m_worldBounds = std::move(bounds); }

    virtual void onCollide(PhysicsBody* collideBody) {}

protected:
    const cocos2d::Rect& getWorldBounds() const { return m_worldBounds; }

private:
    cocos2d::Rect m_worldBounds;
    cocos2d::Vec2 m_velocity{0.0f, 0.0f};
    cocos2d::Vec2 m_acceleration{0.0f, 0.0f};
    bool m_collisionsEnabled{true};
};
