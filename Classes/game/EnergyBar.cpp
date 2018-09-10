//
//  EnergyBar.cpp
//  shooting
//
//  Created by Boris Tsarev on 10/09/2018.
//

#include "EnergyBar.hpp"

USING_NS_CC;

bool EnergyBar::init()
{
    if (!Node::init())
        return false;

    const auto background = Sprite::create("bar_background.png");
    background->setAnchorPoint({0.0f, 0.0f});
    addChild(background);

    m_progressNode = ProgressTimer::create(Sprite::create("bar.png"));
    m_progressNode->setAnchorPoint({0.5f, 0.5f});
    m_progressNode->setPosition({background->getContentSize().width * 0.5f, background->getContentSize().height * 0.5f});
    m_progressNode->setType(ProgressTimer::Type::BAR);
    m_progressNode->setMidpoint({0.0f, 0.5f});
    m_progressNode->setBarChangeRate({1.0f, 0.0f});
    addChild(m_progressNode);

    setContentSize(background->getContentSize());
    return true;
}

void EnergyBar::setPercent(float percent)
{
    m_progressNode->setPercentage(clampf(percent, 0.0f, 100.0f));
}
