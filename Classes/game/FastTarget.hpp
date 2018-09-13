//
//  FastTarget.hpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#pragma once

#include "Target.hpp"

class FastTarget : public Target
{
public:
    bool init(int baseSpeed, cocos2d::Rect worldBounds);
    static FastTarget* create(int baseSpeed, cocos2d::Rect worldBounds);
    ~FastTarget();

    cocos2d::Rect getCollisionBox() const override;

private:
    cocos2d::Node* createAnimatedImage();

    cocos2d::Node* getBackground() const override { return m_background; }
    
    int getMaxHealth() override { return 1; }
    int getHitPoints() override { return 0; }
    int getKillPoints() override { return 15; }

    cocos2d::Node* m_background;
};
