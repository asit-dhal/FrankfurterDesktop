#include "MainComponent.h"
#include "Utility.h"
#include <json.hpp>
#include <iostream>
#include <sstream>

MainComponent::MainComponent(): m_threadPool(3)
                              , m_req("http://api.openrates.io")
{
    
    m_currencyLabel.setJustificationType (Justification::centred);
    m_dateLabel.setJustificationType (Justification::centred);
    
    m_currencyLabel.setFont (Font (16.0f, Font::bold));
    m_dateLabel.setFont (Font (16.0f, Font::bold));
    addAndMakeVisible(&m_currencyLabel);
    addAndMakeVisible(&m_dateLabel);
    
    setSize (600, 400);
    
    m_req.setGet("latest");
    m_req.addListener(this);
    m_threadPool.addJob(&m_req, false);
    TRACE_CLS_LINE(MainComponent);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    
    auto titleHeight = 30;
    m_currencyLabel.setBounds(area.removeFromTop(titleHeight).reduced(10));
    m_dateLabel.setBounds(area.removeFromTop(titleHeight).reduced(10));
}

void MainComponent::exitSignalSent()
{
    TRACE_CLS_LINE(MainComponent);
    auto response = m_req.getLastResponse().rates;
    TRACE_CLS(MainComponent, "Rates: " + String(response.stringify()));
    
    auto baseCurrencyText = "Base Currency: " + String(describe(response.getBaseCurrency()));
    auto dateTimeText = "Foreign Exchange reference rates on " +response.getDateTime().toString(true, false);
    m_currencyLabel.setText(baseCurrencyText, dontSendNotification);
    m_dateLabel.setText(dateTimeText, dontSendNotification);   
}
