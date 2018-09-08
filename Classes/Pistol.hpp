//
//  Pistol.hpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#pragma once

#include <memory>
#include <functional>
#include "cocos2d.h"

class CollisionDetector;
class Bullet;

class Pistol : public cocos2d::Node
{
public:
    using BulletGeneratedHandler = std::function<void(Bullet*)>;

    CREATE_FUNC(Pistol);
    bool init() override;
    bool init(std::weak_ptr<CollisionDetector> collisionDetector);
    static Pistol* create(std::weak_ptr<CollisionDetector> collisionDetector);

    void setBulletGeneratedHandler(BulletGeneratedHandler handler) { m_bulletGeneratedHandler = std::move(handler); }

    void shoot();
    void reset();

private:
    std::weak_ptr<CollisionDetector> m_collisionDetector;
    BulletGeneratedHandler m_bulletGeneratedHandler;
};
