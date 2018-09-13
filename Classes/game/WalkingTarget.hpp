//
//  WalkingTarget.hpp
//  shooting
//
//  Created by Boris Tsarev on 13/09/2018.
//

#pragma once

#include "Target.hpp"

class WalkingTarget : public Target
{
public:
    bool init(int baseSpeed, cocos2d::Rect worldBounds);
    static WalkingTarget* create(int baseSpeed, cocos2d::Rect worldBounds);
    ~WalkingTarget();

    cocos2d::Rect getCollisionBox() const override;

private:
    cocos2d::Node* createAnimatedImage();

    cocos2d::Node* getBackground() const override { return m_background; }

    int getMaxHealth() override { return 3; }
    int getHitPoints() override { return 2; }
    int getKillPoints() override { return 30; }

    cocos2d::Node* m_background;
};
