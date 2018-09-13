//
//  SimpleTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "SimpleTarget.hpp"
#include "Bullet.hpp"
#include "Helpers.hpp"

USING_NS_CC;

bool SimpleTarget::init(int baseSpeed, cocos2d::Rect worldBounds)
{
    if (!Target::init())
        return false;

    setWorldBounds(std::move(worldBounds));

    m_background = createAnimatedImage();
    addChild(m_background);

    // Random position by X and Y.
    const auto positionX = random(-300.0f, 400.0f);
    const auto positionY = random(getWorldBounds().getMinY(), getWorldBounds().getMaxY() - getContentSize().height);
    setPosition(positionX, positionY);

    // Random velocity by X and Y.
    const auto velocityX = random(std::min(10.0f, baseSpeed - 20.0f), baseSpeed + 20.0f);
    const auto velocityY = random(std::min(20.0f, baseSpeed - 30.0f), baseSpeed + 30.0f) * (rand_0_1() > 0.5f ? -1.0f : 1.0f);
    setVelocity({velocityX, velocityY});

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(m_background->getContentSize());
    return true;
}

Node* SimpleTarget::createAnimatedImage()
{
    const auto frames = getAnimationFrames("fly2_%d.png", 4);
    auto image = Sprite::createWithSpriteFrame(frames.front());
    image->setAnchorPoint({0.0f, 0.0f});

    scheduleOnce([image, frames](float) {
        const auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 25);
        const auto flySequence = Sequence::create(Animate::create(animation), Animate::create(animation)->reverse(), nullptr);
        image->runAction(RepeatForever::create(flySequence));
    }, random(0.0f, 1.0f / 5), StringUtils::format("fly %p", this));

    return image;
}

SimpleTarget* SimpleTarget::create(int baseSpeed, cocos2d::Rect worldBounds)
{
    SimpleTarget* target = new (std::nothrow)SimpleTarget();
    if (target && target->init(baseSpeed, std::move(worldBounds))) {
        target->autorelease();
        return target;
    }
    CC_SAFE_DELETE(target);
    return nullptr;
}

SimpleTarget::~SimpleTarget()
{
    log("Simple Target is destroyed");
}

void SimpleTarget::update(float delta)
{
    Target::update(delta);

    if (getPositionY() <= getWorldBounds().getMinY() || getWorldBounds().getMaxY() - getContentSize().height <= getPositionY())
        changeMovingDirection();
}

Rect SimpleTarget::getCollisionBox() const
{
    return Rect(getPosition() + Vec2{8.0f, 6.0f}, Size{34.0f, 30.0f});
}

void SimpleTarget::onCollide(PhysicsBody* collideBody)
{
    Target::onCollide(collideBody);
    if (auto collideTarget = dynamic_cast<SimpleTarget*>(collideBody))
        onCollide(collideTarget);
}

void SimpleTarget::onCollide(SimpleTarget* collideTarget)
{
    // Simple targets bounces off another simple target.
    if (getPositionY() > collideTarget->getPositionY() && getVelocity().y < 0) {
        changeMovingDirection();
        if (collideTarget->getVelocity().y > 0) {
            collideTarget->changeMovingDirection();
        }
    } else if (getPositionY() < collideTarget->getPositionY() && getVelocity().y > 0) {
        changeMovingDirection();
        if (collideTarget->getVelocity().y < 0) {
            collideTarget->changeMovingDirection();
        }
    }
}

void SimpleTarget::changeMovingDirection()
{
    setVelocity({getVelocity().x, -getVelocity().y});
}
