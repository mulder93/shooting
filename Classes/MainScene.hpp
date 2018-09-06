//
//  MainScene.hpp
//  shooting-mobile
//
//  Created by Boris Tsarev on 02/09/2018.
//

#pragma once

#include "cocos2d.h"
#include "CollisionDetector.hpp"

class MainScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(MainScene);
    bool init() override;

    void update(float delta) override;

private:
    CollisionDetector m_collisionDetector;
};
