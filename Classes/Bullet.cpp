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

Bullet::~Bullet()
{
    log("Bullet is destroyed");
}

void Bullet::update(float delta)
{
    PhysicsBody::update(delta);

    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto worldPosition = getParent()->convertToWorldSpace(getPosition());
    const auto size = getContentSize();

    if (worldPosition.x + size.width < 0 || worldPosition.x - size.width > screenSize.width ||
        worldPosition.y + size.height < 0 || worldPosition.y - size.height > screenSize.height) {
        removeFromParent();
    }
}

Rect Bullet::getCollisionBox() const
{
    return getBoundingBox();
}

void Bullet::onCollide(PhysicsBody* collideBody)
{

}
