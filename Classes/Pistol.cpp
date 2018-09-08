//
//  Pistol.cpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#include "Pistol.hpp"
#include "Bullet.hpp"
#include "CollisionDetector.hpp"

USING_NS_CC;

bool Pistol::init()
{
    return Pistol::init(std::shared_ptr<CollisionDetector>());
}

bool Pistol::init(std::weak_ptr<CollisionDetector> collisionDetector)
{
    if (!Node::init())
        return false;

    m_collisionDetector = std::move(collisionDetector);

    const auto image = Sprite::create("pistol.png");
    setContentSize(image->getContentSize());

    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    return true;
}

Pistol* Pistol::create(std::weak_ptr<CollisionDetector> collisionDetector)
{
    Pistol* pistol = new (std::nothrow)Pistol();
    if (pistol && pistol->init(std::move(collisionDetector))) {
        pistol->autorelease();
        return pistol;
    }
    CC_SAFE_DELETE(pistol);
    return nullptr;
}

void Pistol::shoot()
{
    const auto bullet = Bullet::create();
    bullet->setPosition({-4.0f, 23.0f});
    bullet->setVelocity({-200.0f, 0.0f});
    bullet->setAcceleration({0.0f, -50.0f});
    addChild(bullet);

    if (auto detector = m_collisionDetector.lock()) {
        detector->registerBody(bullet);
    }
}
