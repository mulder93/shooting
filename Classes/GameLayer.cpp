//
//  GameLayer.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "GameLayer.hpp"
#include "SimpleTarget.hpp"
#include "Pistol.hpp"
#include "CollisionDetector.hpp"

USING_NS_CC;

bool GameLayer::init()
{
    if (!Layer::init())
        return false;

    scheduleUpdate();
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

    const auto background = Sprite::create("background.jpg");
    background->setAnchorPoint({0.0f, 0.0f});
    background->setPosition({0.0f, 0.0f});
    addChild(background);

    m_collisionDetector = std::make_shared<CollisionDetector>(this);

    for (auto i = 0; i < 15; ++i) {
        const auto target = SimpleTarget::create();
        addChild(target);
        m_collisionDetector->registerBody(target);
    }

    const auto screenSize = Director::getInstance()->getVisibleSize();

    m_pistol = Pistol::create(m_collisionDetector);
    m_pistol->setAnchorPoint({0.5f, 0.5f});
    m_pistol->setRotation(20.0f);
    m_pistol->setPosition({screenSize.width - 60.0f, screenSize.height * 0.5f});
    addChild(m_pistol);

    return true;
}

void GameLayer::update(float delta)
{
    m_collisionDetector->update(delta);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    m_pistol->shoot();
    return true;
}
