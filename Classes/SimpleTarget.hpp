//
//  SimpleTarget.hpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#pragma once

#include "PhysicsBody.hpp"

class Bullet;

class SimpleTarget : public PhysicsBody
{
public:
    CREATE_FUNC(SimpleTarget);
    bool init() override;
    ~SimpleTarget();

    void update(float delta) override;

    cocos2d::Rect getCollisionBox() const override;

    void onCollide(PhysicsBody* collideBody) override;

private:
    void onCollide(SimpleTarget* collideTarget);
    void onCollide(Bullet* bullet);

    void changeMovingDirection();
};
