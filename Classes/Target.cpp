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

    return true;
}

void Target::onCollide(PhysicsBody* collideBody)
{
    if (auto bullet = dynamic_cast<Bullet*>(collideBody)) {
        onCollide(bullet);
    }
}

void Target::onCollide(Bullet* bullet)
{
    removeFromParent();

    if (m_hitHandler)
        m_hitHandler(true, getKillPoints());
}
