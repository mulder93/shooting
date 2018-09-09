//
//  CollisionDetector.cpp
//  shooting
//
//  Created by Boris Tsarev on 03/09/2018.
//

#include "CollisionDetector.hpp"

void CollisionDetector::registerBody(PhysicsBody* body)
{
    m_bodies.pushBack(body);
}

void CollisionDetector::update(float delta)
{
    for (int i = 0; i < m_bodies.size() - 1; ++i) {
        for (int j = i + 1; j < m_bodies.size(); ++j) {
            const auto firstBody = m_bodies.at(i);
            const auto secondBody = m_bodies.at(j);
            if (!firstBody->getParent() || !secondBody->getParent())
                continue;

            const auto firstWorldCollisionBox = cocos2d::Rect(
                firstBody->getParent()->convertToWorldSpace(firstBody->getCollisionBox().origin),
                firstBody->getCollisionBox().size);
            const auto secondWorldCollisionBox = cocos2d::Rect(
                secondBody->getParent()->convertToWorldSpace(secondBody->getCollisionBox().origin),
                secondBody->getCollisionBox().size);

            if (firstWorldCollisionBox.intersectsRect(secondWorldCollisionBox)) {
                firstBody->onCollide(secondBody);
                secondBody->onCollide(firstBody);
            }
        }
    }

    auto iterator = m_bodies.begin();
    while (iterator != m_bodies.cend()) {
        if ((*iterator)->getReferenceCount() == 1) {
            iterator = m_bodies.erase(iterator);
        } else {
            ++iterator;
        }
    }
}
