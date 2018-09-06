//
//  Pistol.cpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#include "Pistol.hpp"
#include "Bullet.hpp"

USING_NS_CC;

bool Pistol::init()
{
    if (!Node::init())
        return false;

    const auto image = Sprite::create("pistol.png");
    setContentSize(image->getContentSize());

    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    return true;
}

void Pistol::shoot()
{
    const auto bullet = Bullet::create();
    bullet->setPosition({-4.0f, 23.0f});
    bullet->setVelocity({-50.0f, 0.0f});
    addChild(bullet);
}
