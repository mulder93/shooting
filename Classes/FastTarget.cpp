//
//  FastTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "FastTarget.hpp"

USING_NS_CC;

namespace
{
    constexpr auto hitPoints = 15;
}

bool FastTarget::init()
{
    if (!Target::init())
        return false;

    const auto fly = Sprite::create("fly2.png");
    setContentSize(fly->getContentSize());

    fly->setAnchorPoint({0.0f, 0.0f});
    addChild(fly);

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(fly->getContentSize());

    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto positionY = random(0.0f, screenSize.height - getContentSize().height);
    setPosition(-getContentSize().width, positionY);

    const auto velocityX = random(200.0f, 300.0f);
    setVelocity({velocityX, 0.0f});

    return true;
}

FastTarget::~FastTarget()
{
    log("Fast Target is destroyed");
}
