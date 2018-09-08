//
//  SimpleTarget.hpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#pragma once

#include <functional>
#include "Target.hpp"

class SimpleTarget : public Target
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

    int getMaxHealth() override { return 2; }
    int getHitPoints() override { return 3; }
    int getKillPoints() override { return 7; }

    void changeMovingDirection();
};
