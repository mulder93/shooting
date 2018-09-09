//
//  AppDelegate.hpp
//  shooting
//
//  Created by Boris Tsarev on 02/09/2018.
//

#pragma once

#include "cocos2d.h"

class AppDelegate : private cocos2d::Application
{
public:
    virtual ~AppDelegate() { }

    virtual void initGLContextAttrs();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};
