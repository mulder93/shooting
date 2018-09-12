//
//  Pistol.cpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#include "Pistol.hpp"
#include <cmath>
#include "Bullet.hpp"
#include "Helpers.hpp"

USING_NS_CC;

namespace
{
    constexpr auto energyPerBullet = 15.0f;
    constexpr auto energyRestoringSpeed = 20.0f;
    constexpr auto bulletStartVelocity = 300.0f;
    constexpr auto gravity = -50.0f;
}

bool Pistol::init()
{
    if (!Node::init())
        return false;

    scheduleUpdate();

    const auto image = Sprite::create("pistol.png");
    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    setContentSize(image->getContentSize());
    return true;
}

void Pistol::update(float delta)
{
    // Energy is restoring automatically.
    m_energy = std::min(getMaxEnergy(), m_energy + energyRestoringSpeed * delta);
}

void Pistol::shoot()
{
    if (!m_bulletGeneratedHandler)
        return;

    if (m_energy < energyPerBullet)
        return;
    
    const auto bullet = Bullet::create();
    bullet->setScale(2.0f);
    bullet->setPosition({-4.0f, 23.0f});

    const auto radiansRotation = radiansFromDegrees(getRotation());
    bullet->setVelocity({-bulletStartVelocity * std::cosf(radiansRotation), bulletStartVelocity * std::sinf(radiansRotation)});
    bullet->setAcceleration({0.0f, gravity});

    m_energy -= energyPerBullet;
    m_bulletGeneratedHandler(bullet);
}

void Pistol::reset()
{
    setRotation(0.0f);
    m_energy = getMaxEnergy();
}
