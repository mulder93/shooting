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
            if (!firstBody->areCollisionsEnabled() || !secondBody->areCollisionsEnabled())
                continue;

            if (firstBody->getCollisionBox().intersectsRect(secondBody->getCollisionBox())) {
                firstBody->onCollide(secondBody);
                secondBody->onCollide(firstBody);
            }
        }
    }

    auto iterator = m_bodies.begin();
    while (iterator != m_bodies.cend()) {
        // Emulation of weak-reference for bodies in CollisionDetector.
        if ((*iterator)->getReferenceCount() == 1) {
            iterator = m_bodies.erase(iterator);
        } else {
            ++iterator;
        }
    }
}
