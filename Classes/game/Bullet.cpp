//
//  Bullet.cpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#include "Bullet.hpp"
#include "Target.hpp"

USING_NS_CC;

bool Bullet::init()
{
    if (!PhysicsBody::init())
        return false;

    const auto image = Sprite::create("drop.png");
    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    setContentSize(image->getContentSize());
    return true;
}

Bullet::~Bullet()
{
    log("Bullet is destroyed");
}

void Bullet::update(float delta)
{
    PhysicsBody::update(delta);

    const auto worldPosition = getParent()->convertToWorldSpace(getPosition());
    const auto size = getContentSize();

    // Bullets are destroyed outside screen.
    if (worldPosition.x + size.width < getWorldBounds().getMinX() || worldPosition.x - size.width > getWorldBounds().getMaxX() ||
        worldPosition.y + size.height < getWorldBounds().getMinY() || worldPosition.y - size.height > getWorldBounds().getMaxY()) {
        removeFromParent();
    }
}

Rect Bullet::getCollisionBox() const
{
    return getBoundingBox();
}

void Bullet::onCollide(PhysicsBody* collideBody)
{
    if (dynamic_cast<Target*>(collideBody)) {
        // Bullet is destroyed after hitting target.
        removeFromParent();
    }
}
