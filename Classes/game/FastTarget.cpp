//
//  FastTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "FastTarget.hpp"
#include "Helpers.hpp"

USING_NS_CC;

bool FastTarget::init(int baseSpeed, cocos2d::Rect worldBounds)
{
    if (!Target::init())
        return false;

    setWorldBounds(std::move(worldBounds));

    m_background = createAnimatedImage();
    addChild(m_background);

    // Random position by Y and off-screen position by X.
    const auto positionY = random(getWorldBounds().getMinY(), getWorldBounds().getMaxY() - getContentSize().height);
    setPosition(-getContentSize().width, positionY);

    // Random velocity by X and no velocity by Y.
    const auto velocityX = random(baseSpeed * 5.0f, baseSpeed * 7.0f);
    setVelocity({velocityX, 0.0f});

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(m_background->getContentSize());
    return true;
}

Node* FastTarget::createAnimatedImage()
{
    const auto frames = getAnimationFrames("fly4_%d.png", 4);
    auto image = Sprite::createWithSpriteFrame(frames.front());
    image->setAnchorPoint({0.0f, 0.0f});

    scheduleOnce([image, frames](float) {
        const auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 25);
        const auto flySequence = Sequence::create(Animate::create(animation), Animate::create(animation)->reverse(), nullptr);
        image->runAction(RepeatForever::create(flySequence));
    }, random(0.0f, 1.0f / 5), StringUtils::format("fly %p", this));

    return image;
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

Rect FastTarget::getCollisionBox() const
{
    return Rect(getPosition() + Vec2{12.0f, 11.0f}, Size{45.0f, 40.0f});
}
