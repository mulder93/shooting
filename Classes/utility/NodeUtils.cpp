//
//  NodeUtils.cpp
//  shooting
//
//  Created by Boris Tsarev on 09/09/2018.
//

#include "NodeUtils.hpp"

USING_NS_CC;

void convertToAnotherNodeSpace(Node* targetNode, const Node* oldSpaceNode, const Node* newSpaceNode)
{
    if (!targetNode || !oldSpaceNode || !newSpaceNode)
        return;

    targetNode->setPosition(newSpaceNode->convertToNodeSpace(oldSpaceNode->convertToWorldSpace(targetNode->getPosition())));
}
