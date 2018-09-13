//
//  WalkingTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 13/09/2018.
//

#include "WalkingTarget.hpp"
#include "Helpers.hpp"

USING_NS_CC;

bool WalkingTarget::init(int baseSpeed, cocos2d::Rect worldBounds)
{
    if (!Target::init())
        return false;

    setWorldBounds(std::move(worldBounds));

    m_background = createAnimatedImage();
    addChild(m_background);

    // Zero-left position at the world bottom (ground).
    setPosition(-m_background->getContentSize().width, getWorldBounds().getMinY());

    // Random velocity by X and no velocity by Y.
    const auto velocityX = random(baseSpeed * 0.5f, baseSpeed * 0.7f);
    setVelocity({velocityX, 0.0f});

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(m_background->getContentSize());
    return true;
}

Node* WalkingTarget::createAnimatedImage()
{
    const auto frames = getAnimationFrames("fly5_%d.png", 5);
    auto image = Sprite::createWithSpriteFrame(frames.front());
    image->setAnchorPoint({0.0f, 0.0f});

    scheduleOnce([image, frames](float) {
        const auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 25);
        const auto flySequence = Sequence::create(Animate::create(animation), Animate::create(animation)->reverse(), nullptr);
        image->runAction(RepeatForever::create(flySequence));
    }, random(0.0f, 1.0f / 5), StringUtils::format("fly %p", this));

    return image;
}

WalkingTarget* WalkingTarget::create(int baseSpeed, cocos2d::Rect worldBounds)
{
    WalkingTarget* target = new (std::nothrow)WalkingTarget();
    if (target && target->init(baseSpeed, std::move(worldBounds))) {
        target->autorelease();
        return target;
    }
    CC_SAFE_DELETE(target);
    return nullptr;
}

WalkingTarget::~WalkingTarget()
{
    log("Walking Target is destroyed");
}

Rect WalkingTarget::getCollisionBox() const
{
    return Rect(getPosition() + Vec2{12.0f, 8.0f}, Size{38.0f, 42.0f});
}
