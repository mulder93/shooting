//
//  GameLayer.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "GameLayer.hpp"
#include <cmath>
#include "SimpleTarget.hpp"
#include "Pistol.hpp"
#include "CollisionDetector.hpp"
#include "FastTarget.hpp"
#include "Bullet.hpp"

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

    m_touchListener = EventListenerTouchOneByOne::create();
    m_touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    m_touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);

    m_mouseListener = EventListenerMouse::create();
    m_mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_mouseListener, this);

    addChild(createBackground());

    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto barBackground = Sprite::create("bar_background.png");
    barBackground->setAnchorPoint({0.0f, 1.0f});
    barBackground->setPosition({5.0f, screenSize.height - 5.0f});
    addChild(barBackground);

    const auto bar = Sprite::create("bar.png");
    bar->setAnchorPoint({0.0f, 0.5f});

    m_energyBar = ProgressTimer::create(bar);
    m_energyBar->setAnchorPoint({0.5f, 0.5f});
    m_energyBar->setPosition({barBackground->getContentSize().width * 0.5f, barBackground->getContentSize().height * 0.5f});
    m_energyBar->setType(ProgressTimer::Type::BAR);
    m_energyBar->setMidpoint({0.0f, 0.5f});
    m_energyBar->setBarChangeRate({1.0f, 0.0f});
    barBackground->addChild(m_energyBar);

    m_pistol = createPistol();
    m_pistol->setBulletGeneratedHandler([this](Bullet* bullet) {
        const auto bulletPosition = m_targetsHolder->convertToNodeSpace(m_pistol->convertToWorldSpace(bullet->getPosition()));
        bullet->setPosition(bulletPosition);
        m_targetsHolder->addChild(bullet);
    });
    addChild(m_pistol);

    m_targetsHolder = createTargetsHolder();
    addChild(m_targetsHolder);

    m_scoreLabel = createScoreLabel();
    addChild(m_scoreLabel);

    m_timerLabel = createTimerLabel();
    addChild(m_timerLabel);

    m_resultLabel = createResultLabel();
    addChild(m_resultLabel);

    startGame();

    return true;
}

GameLayer::~GameLayer()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_mouseListener);
}

void GameLayer::startGame()
{
    m_score = 0;
    updateScoreLabel();

    m_timeLeft = 30.0f;
    updateTimerLabel();

    m_pistol->reset();
    resetTargets();

    m_resultLabel->setVisible(false);
    m_playing = true;
}

void GameLayer::endGame()
{
    m_targetsHolder->unscheduleAllCallbacks();
    m_playing = false;
    showResults();
}

Pistol* GameLayer::createPistol()
{
    const auto pistol = Pistol::create(m_collisionDetector);
    pistol->setAnchorPoint({0.8f, 0.5f});

    const auto screenSize = Director::getInstance()->getVisibleSize();
    pistol->setPosition({screenSize.width - 20.0f, screenSize.height * 0.5f});

    return pistol;
}

void GameLayer::resetTargets()
{
    m_targetsHolder->removeAllChildrenWithCleanup(true);
    
    for (auto i = 0; i < 30; ++i) {
        const auto target = SimpleTarget::create();
        target->setHitHandler([this](bool killed, int points) {
            m_score += points;
            updateScoreLabel();

//            if (m_targetsHolder->getChildrenCount() == 0) {
//                endGame();
//            }
        });

        m_targetsHolder->addChild(target);
        m_collisionDetector->registerBody(target);
    }

    for (auto i = 0; i < 5; ++i) {
        m_targetsHolder->scheduleOnce([this](float) {
            const auto target = FastTarget::create();
            target->setHitHandler([this](bool killed, int points) {
                m_score += points;
                updateScoreLabel();

//                if (m_targetsHolder->getChildrenCount() == 0) {
//                    endGame();
//                }
            });
            m_targetsHolder->addChild(target);
            m_collisionDetector->registerBody(target);
        }, random(0.0f, m_timeLeft - 2.0f), std::string("fast_target") + std::to_string(i));
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
    if (!m_playing)
        return;

    m_collisionDetector->update(delta);
    m_energyBar->setPercentage(100.0f * m_pistol->getEnergy() / m_pistol->getMaxEnergy());

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

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    onInputMoved(touch->getLocation(), touch->getPreviousLocation());
}

void GameLayer::onMouseMoved(EventMouse* event)
{
    const auto mousePosition = Vec2(event->getCursorX(), event->getCursorY());
    const auto delta = m_pistol->getPosition() - mousePosition;
    const auto angleRadians = -std::atanf(delta.y / delta.x);
    const auto angleDegrees = std::max(-60.0f, std::min(60.0f, angleRadians * 180.0f / static_cast<float>(M_PI)));
    m_pistol->setRotation(angleDegrees);
}

void GameLayer::onInputMoved(const Vec2& location, const Vec2& previousLocation)
{
    if (!m_playing)
        return;

    const auto angleDiff = (location.y - previousLocation.y) * 1.5f;
    const auto newAngle = std::max(-60.0f, std::min(60.0f, m_pistol->getRotation() + angleDiff));
    m_pistol->setRotation(newAngle);
}
