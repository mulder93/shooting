//
//  Target.cpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "Target.hpp"
#include "Bullet.hpp"

USING_NS_CC;

namespace
{
    const Color3B hitColor{77, 174, 216};
}

bool Target::init()
{
    if (!PhysicsBody::init())
        return false;
    
    m_health = getMaxHealth();

    return true;
}

void Target::update(float delta)
{
    PhysicsBody::update(delta);

    const auto worldPosition = getParent()->convertToWorldSpace(getPosition());
    const auto size = getContentSize();

    // Targets are destroyed outside screen to the right.
    // (because for now all targets are created on the left and moving to the right)
    if (worldPosition.x - size.width > getWorldBounds().getMaxX())
        removeFromParent();
}

void Target::onCollide(PhysicsBody* collideBody)
{
    if (auto bullet = dynamic_cast<Bullet*>(collideBody))
        onCollide(bullet);
}

void Target::onCollide(Bullet* bullet)
{
    m_health--;
    const bool killed = (m_health <= 0);

    if (m_hitHandler)
        m_hitHandler(killed, killed ? getKillPoints() : getHitPoints());

    if (killed) {
        setCollisionsEnabled(false);
        setVelocity({0.0f, 0.0f});
        getBackground()->stopAllActions();

        const auto removeSelf = ActionFloat::create(0.0f, 0.0f, 0.0f, [this](auto) { removeFromParent(); });
        const auto hit = Spawn::create(TintTo::create(0.05f, hitColor), FadeOut::create(0.15f), nullptr);
        getBackground()->runAction(Sequence::create(hit, removeSelf, nullptr));
    } else {
        const auto hit = Spawn::create(TintTo::create(0.05f, hitColor), ScaleTo::create(0.05f, 1.15f), nullptr);
        const auto normal = Spawn::create(ScaleTo::create(0.05f, 1.0f),TintTo::create(0.05f, Color3B::WHITE), nullptr);
        getBackground()->runAction(Sequence::create(hit, normal, nullptr));
    }
}
