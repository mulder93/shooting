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

namespace
{
    auto createBackground()
    {
        const auto background = Sprite::create("background.jpg");
        background->setAnchorPoint({0.0f, 0.0f});
        return background;
    }

    auto createTargetsHolder()
    {
        const auto holder = cocos2d::Node::create();
        holder->setAnchorPoint({0.0f, 0.0f});
        holder->setPosition({0.0f, 0.0f});
        holder->setContentSize(Director::getInstance()->getVisibleSize());
        return holder;
    }

    auto createHudLabel(float offsetX)
    {
        const auto label = Label::createWithTTF("", "fonts/arial.ttf", 20.0f);
        label->setAnchorPoint({0.0f, 1.0f});

        const auto screenSize = Director::getInstance()->getVisibleSize();
        label->setPosition(Vec2(screenSize.width, screenSize.height) - Vec2(offsetX, 1.0f));

        return label;
    }

    auto createScoreLabel()
    {
        return createHudLabel(100.0f);
    }

    auto createTimerLabel()
    {
        return createHudLabel(200.0f);
    }

    auto createResultLabel()
    {
        const auto label = Label::createWithTTF("", "fonts/arial.ttf", 30.0f);
        label->setAnchorPoint({0.5f, 0.5f});

        const auto screenSize = Director::getInstance()->getVisibleSize();
        label->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height * 0.5f));

        label->setVisible(false);
        label->setAlignment(TextHAlignment::CENTER);
        label->setTextColor(Color4B::BLACK);
        return label;
    }
}

bool GameLayer::init()
{
    if (!Layer::init())
        return false;

    scheduleUpdate();
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    m_collisionDetector = std::make_shared<CollisionDetector>(this);

    addChild(createBackground());
    
    m_targetsHolder = createTargetsHolder();
    addChild(m_targetsHolder);

    m_scoreLabel = createScoreLabel();
    addChild(m_scoreLabel);

    m_timerLabel = createTimerLabel();
    addChild(m_timerLabel);

    m_resultLabel = createResultLabel();
    addChild(m_resultLabel);

    m_pistol = createPistol();
    addChild(m_pistol);

    startGame();

    return true;
}

void GameLayer::startGame()
{
    m_score = 0;
    updateScoreLabel();

    m_timeLeft = 5.0f;
    updateTimerLabel();

    m_pistol->reset();
    resetTargets();

    m_resultLabel->setVisible(false);
    m_playing = true;
}

void GameLayer::endGame()
{
    m_playing = false;
    showResults();
}

Pistol* GameLayer::createPistol()
{
    const auto pistol = Pistol::create(m_collisionDetector);
    pistol->setAnchorPoint({0.5f, 0.5f});
    pistol->setRotation(20.0f);

    const auto screenSize = Director::getInstance()->getVisibleSize();
    pistol->setPosition({screenSize.width - 60.0f, screenSize.height * 0.5f});

    return pistol;
}

void GameLayer::resetTargets()
{
    m_targetsHolder->removeAllChildrenWithCleanup(true);
    
    for (auto i = 0; i < 15; ++i) {
        const auto target = SimpleTarget::create();
        target->setHitHandler([this](int points) {
            m_score += points;
            updateScoreLabel();

            if (m_targetsHolder->getChildrenCount() == 0) {
                endGame();
            }
        });

        m_targetsHolder->addChild(target);
        m_collisionDetector->registerBody(target);
    }
}

void GameLayer::updateScoreLabel()
{
    m_scoreLabel->setString(std::string("Score: ") + std::to_string(m_score));
}

void GameLayer::updateTimerLabel()
{
    const auto secondsLeft = static_cast<int>(std::ceilf(m_timeLeft));
    m_timerLabel->setString(std::string("Time: ") + std::to_string(secondsLeft));
}

void GameLayer::showResults()
{
    const auto resultString = std::string("Final score: ") + std::to_string(m_score) + std::string("\nTap to restart");
    m_resultLabel->setString(resultString);
    m_resultLabel->setVisible(true);
}

void GameLayer::update(float delta)
{
    m_collisionDetector->update(delta);

    m_timeLeft = std::max(0.0f, m_timeLeft - delta);
    updateTimerLabel();

    if (m_timeLeft <= FLT_EPSILON)
        endGame();
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    if (m_playing) {
        m_pistol->shoot();
    } else {
        startGame();
    }

    return true;
}
