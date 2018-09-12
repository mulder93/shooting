//
//  Helpers.cpp
//  shooting
//
//  Created by Boris Tsarev on 09/09/2018.
//

#include "Helpers.hpp"
#include <cmath>

USING_NS_CC;

void convertToAnotherNodeSpace(Node* targetNode, const Node* oldSpaceNode, const Node* newSpaceNode)
{
    if (!targetNode || !oldSpaceNode || !newSpaceNode)
        return;

    targetNode->setPosition(newSpaceNode->convertToNodeSpace(oldSpaceNode->convertToWorldSpace(targetNode->getPosition())));
}

float radiansFromDegrees(float angle)
{
    return angle * static_cast<float>(M_PI) / 180.0f;
}

float degreesFromRadians(float angle)
{
    return angle * 180.0f / static_cast<float>(M_PI);
}

Vector<SpriteFrame*> getAnimationFrames(const std::string& nameFormat, int count)
{
    const auto spriteCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= count; i++) {
        frames.pushBack(spriteCache->getSpriteFrameByName(StringUtils::format(nameFormat.c_str(), i)));
    }
    return frames;
}
