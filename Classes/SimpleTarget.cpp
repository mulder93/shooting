//
//  SimpleTarget.cpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "SimpleTarget.hpp"
#include "Bullet.hpp"

USING_NS_CC;

namespace
{
    constexpr auto hitPoints = 10;
}

bool SimpleTarget::init()
{
    if (!PhysicsBody::init())
        return false;

    const auto fly = Sprite::create("fly.png");
    setContentSize(fly->getContentSize());

    fly->setAnchorPoint({0.0f, 0.0f});
    addChild(fly);

    setAnchorPoint({0.0f, 0.0f});
    setContentSize(fly->getContentSize());

    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto positionX = random(0.0f, 200.0f);
    const auto positionY = random(0.0f, screenSize.height - getContentSize().height);
    setPosition(positionX, positionY);

    const auto velocityY = random(10.0f, 30.0f) * (rand_0_1() > 0.5f ? -1.0f : 1.0f);
    setVelocity({0.0f, velocityY});

    return true;
}

SimpleTarget::~SimpleTarget()
{
    log("Simple Target is destroyed");
}

void SimpleTarget::update(float delta)
{
    PhysicsBody::update(delta);

    const auto screenSize = Director::getInstance()->getVisibleSize();
    if (getPositionY() <= 0 || screenSize.height - getContentSize().height <= getPositionY())
        changeMovingDirection();
}

Rect SimpleTarget::getCollisionBox() const
{
    return Rect(getPosition() + Vec2{5.0f, 5.0f}, getContentSize() - Size{10.0f, 13.0f});
}

void SimpleTarget::onCollide(PhysicsBody* collideBody)
{
    if (auto collideTarget = dynamic_cast<SimpleTarget*>(collideBody)) {
        onCollide(collideTarget);
    } else if (auto bullet = dynamic_cast<Bullet*>(collideBody)) {
        onCollide(bullet);
    }
}

void SimpleTarget::onCollide(SimpleTarget* collideTarget)
{
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

void SimpleTarget::onCollide(Bullet* bullet)
{
    if (m_hitHandler)
        m_hitHandler(hitPoints);

    removeFromParent();
}

void SimpleTarget::changeMovingDirection()
{
    setVelocity({getVelocity().x, -getVelocity().y});
}
