//
//  Bullet.cpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#include "Bullet.hpp"

USING_NS_CC;

bool Bullet::init()
{
    if (!PhysicsBody::init())
        return false;

    const auto image = Sprite::create("drop.png");
    setContentSize(image->getContentSize());

    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    return true;
}

void Bullet::update(float delta)
{
    PhysicsBody::update(delta);
}

Rect Bullet::getCollisionBox() const
{
    return getBoundingBox();
}

void Bullet::onCollide(PhysicsBody* collideBody)
{

}
