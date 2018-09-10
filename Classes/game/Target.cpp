//
//  Target.cpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "Target.hpp"
#include "Bullet.hpp"

USING_NS_CC;

bool Target::init()
{
    if (!PhysicsBody::init())
        return false;

    m_health = getMaxHealth();

    return true;
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

    if (killed)
        removeFromParent();
}
