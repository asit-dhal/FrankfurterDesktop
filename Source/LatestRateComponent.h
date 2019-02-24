/*
  ==============================================================================

    LatestRateComponent.h
    Created: 18 Feb 2019 2:18:25am
    Author:  asitd

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JsonRequest.h"
#include "LatestRateModel.h"

class LatestRateComponent :
    public Component,
    public LatestRateModel::Listener
{
public:

    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void dataUpdated() = 0;
        virtual void statusChanged(String message) = 0;
    };

    LatestRateComponent();
    ~LatestRateComponent();

    void paint (Graphics&) override;
    void resized() override;
    void modelUpdated() override;
    void addListener(Listener* listener);
    void informListener();

private:
    TableListBox m_table{ {}, nullptr };
    Font font{ 14.0f };
    std::vector<Listener*> m_listeners;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LatestRateComponent)
};
