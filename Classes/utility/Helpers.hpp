//
//  Helpers.hpp
//  shooting
//
//  Created by Boris Tsarev on 09/09/2018.
//

#pragma once

#include "cocos2d.h"

void convertToAnotherNodeSpace(cocos2d::Node* targetNode, const cocos2d::Node* oldSpaceNode, const cocos2d::Node* newSpaceNode);

float radiansFromDegrees(float angle);
float degreesFromRadians(float angle);

cocos2d::Vector<cocos2d::SpriteFrame*> getAnimationFrames(const std::string& nameFormat, int count);
