//
//  EventListenerHolder.hpp
//  shooting
//
//  Created by Boris Tsarev on 09/09/2018.
//

#pragma once

#include "cocos2d.h"

class EventListenerHolder
{
public:
    ~EventListenerHolder();

    void addListener(cocos2d::EventListener* listener, cocos2d::Node* node);

private:
    cocos2d::Vector<cocos2d::EventListener*> m_listeners;
};
