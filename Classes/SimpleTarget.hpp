//
//  SimpleTarget.hpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#pragma once

#include <functional>
#include "PhysicsBody.hpp"

class Bullet;

class SimpleTarget : public PhysicsBody
{
public:
    using HitHandler = std::function<void(int points)>;

    CREATE_FUNC(SimpleTarget);
    bool init() override;
    ~SimpleTarget();

    void update(float delta) override;

    cocos2d::Rect getCollisionBox() const override;
    void onCollide(PhysicsBody* collideBody) override;

    void setHitHandler(HitHandler handler) { m_hitHandler = std::move(handler); }

private:
    void onCollide(SimpleTarget* collideTarget);
    void onCollide(Bullet* bullet);

    void changeMovingDirection();

    HitHandler m_hitHandler;
};
