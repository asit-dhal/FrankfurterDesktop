/*
  ==============================================================================

    HistoricalRatePlotComponent.h
    Created: 21 Feb 2019 10:54:30pm
    Author:  asitd

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HistoricalRateModel.h"

class HistoricalRatePlotComponent :
    public Component,
    public HistoricalRateModel::Listener
{
public:
    HistoricalRatePlotComponent();
    ~HistoricalRatePlotComponent();

    void paint (Graphics&) override;
    void resized() override;
    void modelUpdated() override;

private:
    void drawAxesAndGrid(Graphics&);
    void transformDataToCoordinates(Graphics&);
    void plot(Graphics&);

    std::vector<Point<float>> m_coordinates;

    static const int X_OFFSET;
    static const int Y_OFFSET;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistoricalRatePlotComponent)
};
