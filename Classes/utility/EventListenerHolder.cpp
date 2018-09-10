//
//  EventListenerHolder.cpp
//  shooting
//
//  Created by Boris Tsarev on 09/09/2018.
//

#include "EventListenerHolder.hpp"

USING_NS_CC;

EventListenerHolder::~EventListenerHolder()
{
    for (const auto listener : m_listeners)
        Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

void EventListenerHolder::addListener(EventListener* listener, Node* node)
{
    m_listeners.pushBack(listener);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}
