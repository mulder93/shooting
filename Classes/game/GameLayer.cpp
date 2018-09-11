//
//  GameLayer.cpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#include "GameLayer.hpp"
#include <cmath>
#include "SimpleTarget.hpp"
#include "FastTarget.hpp"
#include "Pistol.hpp"
#include "Bullet.hpp"
#include "EnergyBar.hpp"
#include "CollisionDetector.hpp"
#include "Helpers.hpp"

USING_NS_CC;

namespace
{

#pragma mark - Non-member nodes creation

    auto createBackground()
    {
        const auto background = Sprite::create("background.jpg");
        background->setAnchorPoint({0.0f, 0.0f});
        return background;
    }

    auto createEnergyBar()
    {
        const auto bar = EnergyBar::create();
        bar->setAnchorPoint({0.0f, 1.0f});
        bar->setPosition({5.0f, Director::getInstance()->getVisibleSize().height - 5.0f});
        return bar;
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

#pragma mark -

}

#pragma mark - Initialization and nodes creation

bool GameLayer::init()
{
    if (!Layer::init())
        return false;

    scheduleUpdate();

    m_collisionDetector = std::make_shared<CollisionDetector>();
    m_eventListenerHolder.addListener(createTouchListener(), this);
    m_eventListenerHolder.addListener(createMouseListener(), this);

    addChild(createBackground());

    m_energyBar = createEnergyBar();
    addChild(m_energyBar);

    m_pistol = createPistol();
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

Pistol* GameLayer::createPistol() const
{
    const auto pistol = Pistol::create();
    pistol->setAnchorPoint({0.8f, 0.5f});

    const auto screenSize = Director::getInstance()->getVisibleSize();
    pistol->setPosition({screenSize.width - 20.0f, screenSize.height * 0.5f});

    pistol->setBulletGeneratedHandler([this](Bullet* bullet) {
        convertToAnotherNodeSpace(bullet, m_pistol, m_targetsHolder);
        m_targetsHolder->addChild(bullet);
        m_collisionDetector->registerBody(bullet);
    });

    return pistol;
}

void GameLayer::resetTargets()
{
    m_targetsHolder->removeAllChildrenWithCleanup(true);

    for (auto i = 0; i < m_configuration.getTargetsCount(); ++i) {
        addTarget(SimpleTarget::create(m_configuration.getSpeed()));
    }

    for (auto i = 0; i < 5; ++i) {
        const auto scheduleKey = StringUtils::format("fast_target_%d", i);
        m_targetsHolder->scheduleOnce([this](float) {
            addTarget(FastTarget::create());
        }, random(0.0f, m_timeLeft - 2.0f), scheduleKey);
    }
}

void GameLayer::addTarget(Target* target)
{
    target->setHitHandler([this](bool killed, int points) {
        m_score += points;
        updateScoreLabel();
    });

    m_targetsHolder->addChild(target);
    m_collisionDetector->registerBody(target);
}

#pragma mark - Game

void GameLayer::startGame()
{
    m_score = 0;
    updateScoreLabel();

    m_timeLeft = m_configuration.getTime();
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

void GameLayer::updateScoreLabel()
{
    m_scoreLabel->setString(StringUtils::format("Score: %d", m_score));
}

void GameLayer::updateTimerLabel()
{
    const auto secondsLeft = static_cast<int>(std::ceilf(m_timeLeft));
    m_timerLabel->setString(StringUtils::format("Time: %d", secondsLeft));
}

void GameLayer::showResults()
{
    m_resultLabel->setString(StringUtils::format("Final score: %d\nTap to restart", m_score));
    m_resultLabel->setVisible(true);
}

void GameLayer::update(float delta)
{
    if (!m_playing)
        return;

    m_collisionDetector->update(delta);
    m_energyBar->setPercent(100.0f * m_pistol->getEnergy() / m_pistol->getMaxEnergy());

    m_timeLeft = std::max(0.0f, m_timeLeft - delta);
    updateTimerLabel();

    if (m_timeLeft <= FLT_EPSILON)
        endGame();
}

#pragma mark - Input

cocos2d::EventListener* GameLayer::createTouchListener()
{
    const auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    return touchListener;
}

cocos2d::EventListener* GameLayer::createMouseListener()
{
    const auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMoved, this);
    return mouseListener;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    if (m_playing) {
        rotatePistol(touch->getLocation());
        m_pistol->shoot();
    } else {
        startGame();
    }
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    rotatePistol(touch->getLocation());
}

void GameLayer::onMouseMoved(EventMouse* event)
{
    rotatePistol({event->getCursorX(), event->getCursorY()});
}

void GameLayer::rotatePistol(const Vec2& inputPosition)
{
    if (inputPosition.x >= m_pistol->getPosition().x)
        return;

    const auto screenSize = Director::getInstance()->getVisibleSize();
    if (inputPosition.x < 0.0f || screenSize.width < inputPosition.x ||
        inputPosition.y < 0.0f || screenSize.height < inputPosition.y)
        return;

    const auto delta = m_pistol->getPosition() - inputPosition;
    const auto angle = degreesFromRadians(-std::atanf(delta.y / delta.x));
    m_pistol->setRotation(clampf(angle, -60.0f, 60.0f));
}
