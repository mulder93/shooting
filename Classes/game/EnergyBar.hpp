//
//  EnergyBar.hpp
//  shooting
//
//  Created by Boris Tsarev on 10/09/2018.
//

#pragma once

#include "cocos2d.h"

class EnergyBar : public cocos2d::Node
{
public:
    CREATE_FUNC(EnergyBar);
    bool init() override;

    void setPercent(float percent);

private:
    cocos2d::ProgressTimer* m_progressNode = nullptr;
};
