//
//  Configuration.hpp
//  shooting
//
//  Created by Boris Tsarev on 11/09/2018.
//

#pragma once

#include <unordered_map>

class Configuration
{
public:
    Configuration();

    int getTargetsCount() { return m_targetsCount; }
    int getFastTargetsCount() { return m_fastTargetsCount; }
    int getWalkingTargetsCount() { return m_walkingTargetsCount; }
    int getSpeed() { return m_speed; }
    int getTime() { return m_time; }

private:
    int getFileValue(const std::string& key, int defaultValue) const;

    std::unordered_map<std::string, int> m_fileParams;

    int m_targetsCount;
    int m_fastTargetsCount;
    int m_walkingTargetsCount;
    int m_speed;
    int m_time;
};
