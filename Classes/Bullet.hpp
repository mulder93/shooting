//
//  Bullet.hpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#pragma once

#include "PhysicsBody.hpp"

class Bullet : public PhysicsBody
{
public:
    CREATE_FUNC(Bullet);
    bool init() override;
    ~Bullet();

    void update(float delta) override;

    cocos2d::Rect getCollisionBox() const override;
    void onCollide(PhysicsBody* collideBody) override;
};
