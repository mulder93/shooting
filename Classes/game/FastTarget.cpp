//
//  FastTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "FastTarget.hpp"

USING_NS_CC;

bool FastTarget::init(int baseSpeed, cocos2d::Rect worldBounds)
{
    if (!Target::init())
        return false;

    setWorldBounds(std::move(worldBounds));

    const auto image = Sprite::create("fly2.png");
    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    // Random position by Y and off-screen position by X.
    const auto positionY = random(getWorldBounds().getMinY(), getWorldBounds().getMaxY() - getContentSize().height);
    setPosition(-getContentSize().width, positionY);

    // Random velocity by X and no velocity by Y.
    const auto velocityX = random(baseSpeed * 5.0f, baseSpeed * 7.0f);
    setVelocity({velocityX, 0.0f});

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(image->getContentSize());
    return true;
}

FastTarget* FastTarget::create(int baseSpeed, cocos2d::Rect worldBounds)
{
    FastTarget* target = new (std::nothrow)FastTarget();
    if (target && target->init(baseSpeed, std::move(worldBounds))) {
        target->autorelease();
        return target;
    }
    CC_SAFE_DELETE(target);
    return nullptr;
}

FastTarget::~FastTarget()
{
    log("Fast Target is destroyed");
}
