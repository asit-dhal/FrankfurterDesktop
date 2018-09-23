#include "MainComponent.h"


MainComponent::MainComponent(): m_threadPool(3)
                              , m_req("http://api.openrates.io")
{
    setSize (600, 400);
    
    m_req.setGet("latest");
    m_req.addListener(this);
    m_threadPool.addJob(&m_req, false);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
}

void MainComponent::resized()
{
}

void MainComponent::exitSignalSent()
{
    Logger::outputDebugString("Job finished");
    Logger::outputDebugString("res: " + m_req.getLastResponse().bodyAsString);
}
