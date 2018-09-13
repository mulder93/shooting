//
//  Target.hpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "PhysicsBody.hpp"

#pragma once

class Bullet;

class Target : public PhysicsBody
{
public:
    using HitHandler = std::function<void(bool killed, int points)>;

    bool init() override;
    void update(float delta) override;

    void onCollide(PhysicsBody* collideBody) override;

    void setHitHandler(HitHandler handler) { m_hitHandler = std::move(handler); }

private:
    void onCollide(Bullet* bullet);
    virtual cocos2d::Node* getBackground() const = 0;

    virtual int getMaxHealth() = 0;
    virtual int getHitPoints() = 0;
    virtual int getKillPoints() = 0;

    HitHandler m_hitHandler;
    int m_health = 0;
};
