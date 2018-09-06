//
//  Pistol.hpp
//  shooting
//
//  Created by Boris Tsarev on 05/09/2018.
//

#pragma once

#include "cocos2d.h"

class Pistol : public cocos2d::Node
{
public:
    CREATE_FUNC(Pistol);
    bool init() override;

    void shoot();
};
