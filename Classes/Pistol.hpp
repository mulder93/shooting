//
//  Pistol.hpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#pragma once

#include "cocos2d.h"
#include <memory>

class CollisionDetector;

class Pistol : public cocos2d::Node
{
public:
    CREATE_FUNC(Pistol);
    bool init() override;
    bool init(std::weak_ptr<CollisionDetector> collisionDetector);
    static Pistol* create(std::weak_ptr<CollisionDetector> collisionDetector);

    void shoot();
    void reset();

private:
    std::weak_ptr<CollisionDetector> m_collisionDetector;
};
