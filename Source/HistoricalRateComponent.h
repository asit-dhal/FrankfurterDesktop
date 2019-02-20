/*
  ==============================================================================

    HistoricalRateComponent.h
    Created: 20 Feb 2019 6:50:46pm
    Author:  asitd

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HistoricalRateModel.h"

class HistoricalRateComponent :
    public Component,
    public HistoricalRateModel::Listener
{
public:
    HistoricalRateComponent();
    ~HistoricalRateComponent();

    void paint (Graphics&) override;
    void resized() override;
    void modelUpdated() override;

private:
    TableListBox m_table{ {}, nullptr };
    Font font{ 14.0f };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistoricalRateComponent)
};
