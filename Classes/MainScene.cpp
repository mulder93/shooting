//
//  MainScene.cpp
//  shooting-mobile
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "MainScene.hpp"
#include "SimpleTarget.hpp"
#include "Pistol.hpp"
#include "CollisionDetector.hpp"

USING_NS_CC;

bool MainScene::init()
{
    if (!Scene::init())
        return false;

    m_collisionDetector = std::make_shared<CollisionDetector>(this);

    scheduleUpdate();

    const auto background = Sprite::create("background.jpg");
    background->setAnchorPoint({0.0f, 0.0f});
    background->setPosition({0.0f, 0.0f});
    addChild(background);

    for (auto i = 0; i < 15; ++i) {
        const auto target = SimpleTarget::create();
        addChild(target);
        m_collisionDetector->registerBody(target);
    }

    const auto screenSize = Director::getInstance()->getVisibleSize();

    const auto pistol = Pistol::create(m_collisionDetector);
    pistol->setAnchorPoint({0.5f, 0.5f});
    pistol->setRotation(20.0f);
    pistol->setPosition({screenSize.width - 60.0f, screenSize.height * 0.5f});
    addChild(pistol);

    schedule([pistol](float) { pistol->shoot(); }, 1.0f, 10, 1.0f, "shoot");

    return true;
}

void MainScene::update(float delta)
{
    m_collisionDetector->update(delta);
}
