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
    void mouseMove(const MouseEvent &event) override;

private:
    void drawAxes(Graphics&);
    void drawGridsAndLabels(Graphics&);
    void transformDataToCoordinates();
    void plot(Graphics&);

    float rateToYCoordinate(float currentRate);
    float yCoordinateToRate(float currentCoordinate);

    std::vector<Point<float>> m_coordinates;
    std::map<Time, float> m_timeToXCoordinateMappings;

    static const int X_OFFSET;
    static const int Y_OFFSET;
    static const int X_GRID_LINE_COUNT;
    static const int Y_GRID_LINE_COUNT;

    float m_xAxisStepValue = 0.0;
    float m_yAxisStepValue = 0.0;
    double m_minRate = 0.0;
    double m_maxRate = 0.0;

    Label m_statueLabel;
    std::vector<Listener*> m_listeners;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistoricalRatePlotComponent)
};
