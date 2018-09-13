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
    bool init(int baseSpeed, cocos2d::Rect worldBounds);
    static SimpleTarget* create(int baseSpeed, cocos2d::Rect worldBounds);

    ~SimpleTarget();

    void update(float delta) override;

    cocos2d::Rect getCollisionBox() const override;
    void onCollide(PhysicsBody* collideBody) override;

private:
    cocos2d::Node* createAnimatedImage();

    cocos2d::Node* getBackground() const override { return m_background; }
    void onCollide(SimpleTarget* collideTarget);

    int getMaxHealth() override { return 1; }
    int getHitPoints() override { return 3; }
    int getKillPoints() override { return 7; }

    void changeMovingDirection();

    cocos2d::Node* m_background;
};
