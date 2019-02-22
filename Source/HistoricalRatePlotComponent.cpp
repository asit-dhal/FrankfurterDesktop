/*
  ==============================================================================

    HistoricalRatePlotComponent.cpp
    Created: 21 Feb 2019 10:54:30pm
    Author:  asitd

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "HistoricalRatePlotComponent.h"

//==============================================================================

const int HistoricalRatePlotComponent::X_OFFSET = 50;
const int HistoricalRatePlotComponent::Y_OFFSET = 50;

HistoricalRatePlotComponent::HistoricalRatePlotComponent()
{
    auto modelInstance = HistoricalRateModel::getInstance();
    modelInstance->addListener(this);
}

HistoricalRatePlotComponent::~HistoricalRatePlotComponent()
{
}

void HistoricalRatePlotComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);

    transformDataToCoordinates(g);
    drawAxesAndGrid(g);
    plot(g);
}

void HistoricalRatePlotComponent::drawAxesAndGrid(Graphics& g)
{
    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();


    Line<float> xAxis(X_OFFSET, height - Y_OFFSET, width - X_OFFSET, height - Y_OFFSET);
    Line<float> yAxis(X_OFFSET, Y_OFFSET, X_OFFSET, height - Y_OFFSET);

    g.drawLine(xAxis, 2);
    g.drawLine(yAxis, 2);

    auto xAxisLength = width - X_OFFSET * 2;
    auto yAxisLength = height - Y_OFFSET * 2;

    // x-grids
    for (auto i = X_OFFSET * 2; i < yAxisLength; i += yAxisLength / 10)
    {
        g.drawLine(X_OFFSET, i, width - X_OFFSET, i, 0.5);
    }
    auto modelData = HistoricalRateModel::getInstance()->getHistoricalRates();
    std::vector<String> xAxisData;
    std::vector<String> yAxisData;
    for (auto const& e : modelData)
    {
        xAxisData.push_back(e.first.formatted(String("%d-%m-%Y")));
    }




    if (xAxisData.empty())
        return;

    auto labelWidth = Font({ 14.0f }).getStringWidth(xAxisData.front());

    auto xAxisStepValue = xAxisLength / (labelWidth * 2);

    // y-axis
    auto yGridLineCnt = 0;
    for (auto i = X_OFFSET + labelWidth + labelWidth /2; i < xAxisLength; i += (labelWidth + labelWidth / 2))
    {
        yGridLineCnt++;
        g.drawLine(i, Y_OFFSET, i, height - Y_OFFSET, 0.5);
    }

    auto stepValue = xAxisData.size() / yGridLineCnt;

    auto index = stepValue;
    for (auto i = X_OFFSET + labelWidth + labelWidth / 2; i < xAxisLength; i += (labelWidth + labelWidth / 2))
    {
        String text = xAxisData.at(index);
        auto textWidth = Font({ 14.0f }).getStringWidth(text);
        auto textHeight = Font({ 14.0f }).getHeight();
        g.drawText(text, i - labelWidth / 2, height - Y_OFFSET + 10, textWidth, textHeight, Justification::centred);
        index += stepValue;
    }

}

void HistoricalRatePlotComponent::transformDataToCoordinates(Graphics& g)
{
    auto modelData = HistoricalRateModel::getInstance()->getHistoricalRates();
    if (modelData.empty())
        return;
    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    auto realWidth = width - 2*X_OFFSET;
    auto realHeight = height - 2*Y_OFFSET;

    DBG("width=" << width << " height=" << width << " realWidth=" << realWidth << " realHeight=" << realHeight);

    m_coordinates.clear();
    m_coordinates.resize(modelData.size());

    auto xAxisStep = realWidth / modelData.size();

    auto i = 0;
    for (auto const& e : modelData)
    {
        m_coordinates[i].setX(X_OFFSET + i * xAxisStep);
        i++;
    }

    std::vector<double> historicalValues;
    for (auto const& e : modelData) {
        historicalValues.push_back(e.second);
    }

    double minY = 0.0, maxY = 0.0;
    auto minMax = std::minmax_element(historicalValues.begin(), historicalValues.end());
    minY = *(std::get<0>(minMax));
    maxY = *(std::get<1>(minMax));

    DBG("minY=" << minY << " maxY=" << maxY);
    i = 0;
    auto rangeY = maxY - minY;
    auto yAxisStep = realHeight / rangeY;
    DBG("yAxis step=" << yAxisStep);

    for (auto const& e : modelData)
    {
        DBG("e.second=" << e.second << " yAxisStep * (e.second-minY)=" << yAxisStep * (e.second - minY));
        m_coordinates[i].setY(realHeight- yAxisStep * (e.second-minY));
        i++;
    }
}

void HistoricalRatePlotComponent::plot(Graphics& g)
{
    g.setColour(Colours::orange);
    Path path;
    if (!m_coordinates.empty())
    {
        DBG("Point: x=" << m_coordinates.front().getX() << " y=" << m_coordinates.front().getY());
        path.startNewSubPath(m_coordinates.front());
        for (auto i = 1; i < m_coordinates.size(); i++)
        {
            DBG("Point: x=" << m_coordinates.at(i).getX() << " y=" << m_coordinates.at(i).getY());
            path.lineTo(m_coordinates.at(i));
        }
    }

    g.strokePath(path, PathStrokeType(1.0f));
}

void HistoricalRatePlotComponent::resized()
{

}

void HistoricalRatePlotComponent::modelUpdated()
{
    repaint();
}
