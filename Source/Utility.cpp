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
