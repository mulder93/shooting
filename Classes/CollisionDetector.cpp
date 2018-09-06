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
            if (m_bodies.at(i)->getCollisionBox().intersectsRect(m_bodies.at(j)->getCollisionBox())) {
                m_bodies.at(i)->onCollide(m_bodies.at(j));
                m_bodies.at(j)->onCollide(m_bodies.at(i));
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
