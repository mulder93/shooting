//
//  MainScene.cpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#include "MainScene.hpp"
#include "GameLayer.hpp"

USING_NS_CC;

bool MainScene::init()
{
    if (!Scene::init())
        return false;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fly.plist");

    addChild(GameLayer::create());

    return true;
}
