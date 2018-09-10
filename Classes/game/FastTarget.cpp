//
//  FastTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "FastTarget.hpp"

USING_NS_CC;

bool FastTarget::init()
{
    if (!Target::init())
        return false;

    const auto image = Sprite::create("fly2.png");
    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    // Random position by Y and off-screen position by X.
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto positionY = random(0.0f, screenSize.height - getContentSize().height);
    setPosition(-getContentSize().width, positionY);

    // Random velocity by X and no velocity by Y.
    const auto velocityX = random(200.0f, 300.0f);
    setVelocity({velocityX, 0.0f});

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(image->getContentSize());
    return true;
}

FastTarget::~FastTarget()
{
    log("Fast Target is destroyed");
}
