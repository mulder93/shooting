//
//  Pistol.cpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#include "Pistol.hpp"
#include <cmath>
#include "Bullet.hpp"

USING_NS_CC;

namespace
{
    constexpr auto energyPerBullet = 15.0f;
    constexpr auto energyRestoringSpeed = 15.0f;
}

bool Pistol::init()
{
    if (!Node::init())
        return false;

    scheduleUpdate();

    const auto image = Sprite::create("pistol.png");
    setContentSize(image->getContentSize());

    image->setAnchorPoint({0.0f, 0.0f});
    addChild(image);

    return true;
}

void Pistol::update(float delta)
{
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
    bullet->setVelocity({-300.0f * std::cosf(getRotation() * M_PI / 180.0f), 300.0f * std::sinf(getRotation() * M_PI / 180.0f)});
    bullet->setAcceleration({0.0f, -50.0f});

    m_energy -= energyPerBullet;
    m_bulletGeneratedHandler(bullet);
}

void Pistol::reset()
{
    setRotation(0.0f);
    m_energy = getMaxEnergy();
    // TODO: remove all bullets
}
