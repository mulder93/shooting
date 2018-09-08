//
//  MainScene.cpp
//  shooting-mobile
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

    const auto gameLayer = GameLayer::create();
    addChild(gameLayer);

    return true;
}
