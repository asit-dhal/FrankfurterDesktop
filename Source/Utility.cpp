/*
  ==============================================================================

    Utility.cpp
    Created: 18 Feb 2019 9:31:06pm
    Author:  asitd

  ==============================================================================
*/

#include "Utility.h"

GlobalInstance::GlobalInstance(): m_threadPool(3)
{
}

ThreadPool& GlobalInstance::getThreadPool()
{
    return m_threadPool;
}

JUCE_IMPLEMENT_SINGLETON(GlobalInstance);

std::vector<std::string> split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}