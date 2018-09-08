//
//  FastTarget.hpp
//  shooting
//
//  Created by Boris Tsarev on 08/09/2018.
//

#pragma once

#include "Target.hpp"

class FastTarget : public Target
{
public:
    CREATE_FUNC(FastTarget);
    bool init() override;
    ~FastTarget();

private:
    int getHitPoints() override { return 0; }
    int getKillPoints() override { return 15; }
};
