//
//  Configuration.cpp
//  shooting
//
//  Created by Boris Tsarev on 11/09/2018.
//

#include "Configuration.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace
{
    const std::string filename = "input.txt";

    // Read line in format "key=value".
    std::pair<std::string, int> readFileLine(const std::string& line)
    {
        // At least 3 characters to support required format.
        if (line.size() < 3)
            return {};

        // Equal sign cannot be at the first or the last symbol.
        const auto equalPosition = line.find_first_of("=");
        if (equalPosition == line.npos || equalPosition == 0 || equalPosition == line.size() - 1)
            return {};

        const std::string key = line.substr(0, equalPosition);
        const int value = std::atoi(line.substr(equalPosition + 1, line.size() - equalPosition - 1).c_str());
        return {key, value};

    }

    std::unordered_map<std::string, int> readFile()
    {
        std::ifstream fileStream;
        fileStream.open(filename);

        if (!fileStream)
            return {};

        std::string line;
        std::unordered_map<std::string, int> result;
        while (std::getline(fileStream, line)) {
            const auto keyValuePair = readFileLine(line);
            if (!keyValuePair.first.empty() && keyValuePair.second > 0) {
                result.insert(keyValuePair);
            }
        }
        fileStream.close();
        return result;
    }
}

Configuration::Configuration()
{
    m_fileParams = readFile();

    m_targetsCount = getFileValue("CountTarget", 10);
    m_fastTargetsCount = getFileValue("CountFastTargets", 5);
    m_walkingTargetsCount = getFileValue("CountWalkingTargets", 1);
    m_speed = getFileValue("Speed", 50);
    m_time = getFileValue("Time", 50);
}

int Configuration::getFileValue(const std::string& key, int defaultValue) const
{
    return m_fileParams.find(key) != m_fileParams.cend() ? m_fileParams.at(key) : defaultValue;
}
