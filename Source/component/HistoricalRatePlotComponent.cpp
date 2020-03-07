/*
 * Copyright (c) 2018-2020 Asit Dhal.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "HistoricalRatePlotComponent.h"

namespace component
{

const int HistoricalRatePlotComponent::X_OFFSET = 100;
const int HistoricalRatePlotComponent::Y_OFFSET = 50;
const int HistoricalRatePlotComponent::X_GRID_LINE_COUNT = 10;
const int HistoricalRatePlotComponent::Y_GRID_LINE_COUNT = 10;

HistoricalRatePlotComponent::HistoricalRatePlotComponent()
{
    m_statueLabel.setFont(Font(16.0f, Font::bold));
    auto modelInstance = model::HistoricalRateModel::getInstance();
    modelInstance->addListener(this);
}

HistoricalRatePlotComponent::~HistoricalRatePlotComponent()
{
    model::HistoricalRateModel::getInstance()->removeListener(this);
}

void HistoricalRatePlotComponent::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::white);
    g.setFont(14.0f);

    auto area = getLocalBounds();

    drawAxes(g);
    if (!model::HistoricalRateModel::getInstance()->getHistoricalRates().empty())
    {
        transformDataToCoordinates();
        drawGridsAndLabels(g);
        plot(g);
    }
}

void HistoricalRatePlotComponent::drawAxes(Graphics& g)
{
    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    Line<float> xAxis(X_OFFSET, height - Y_OFFSET, width - X_OFFSET, height - Y_OFFSET);
    Line<float> yAxis(X_OFFSET, Y_OFFSET, X_OFFSET, height - Y_OFFSET);

    g.drawLine(xAxis, 2);
    g.drawLine(yAxis, 2);
}

void HistoricalRatePlotComponent::drawGridsAndLabels(Graphics& g)
{
    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    auto xAxisLength = width - X_OFFSET * 2;
    auto yAxisLength = height - Y_OFFSET * 2;

    // x-grids
    for (auto i = Y_OFFSET; i < yAxisLength; i += yAxisLength / X_GRID_LINE_COUNT)
    {
        g.drawLine(X_OFFSET, i, width - X_OFFSET, i, 0.5);
        auto rate = yCoordinateToRate(i);
        String text = String(std::to_string(rate));
        auto textWidth = Font({ 14.0f }).getStringWidth(text);
        auto textHeight = Font({ 14.0f }).getHeight();
        g.drawText(text, X_OFFSET - textWidth - 5, i - textHeight / 2, textWidth, textHeight, Justification::centred);

    }

    // y-grids

    auto modelData = model::HistoricalRateModel::getInstance()->getHistoricalRates();
    std::vector<String> xAxisData;
    for (auto const& e : modelData)
    {
        xAxisData.push_back(e.first.formatted(String("%d-%m-%Y")));
    }

    auto labelWidth = Font({ 14.0f }).getStringWidth(xAxisData.front());

    auto index = 0;
    for (auto i = X_OFFSET + labelWidth + labelWidth / 2; i <= width - X_OFFSET; i += (labelWidth + labelWidth / 2))
    {
        g.drawLine(i, Y_OFFSET, i, height - Y_OFFSET, 0.5);

        String text = xAxisData.at(index);
        auto textWidth = Font({ 14.0f }).getStringWidth(text);
        auto textHeight = Font({ 14.0f }).getHeight();
        g.drawText(text, i - labelWidth / 2, height - Y_OFFSET + 10, textWidth, textHeight, Justification::centred);
        index += m_xAxisStepValue;
    }

}

void HistoricalRatePlotComponent::transformDataToCoordinates()
{
    auto modelData = model::HistoricalRateModel::getInstance()->getHistoricalRates();
    if (modelData.empty())
        return;

    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();
    auto realWidth = width - 2 * X_OFFSET;
    auto realHeight = height - 2 * Y_OFFSET;

    DBG("width=" << width << " height=" << width << " realWidth=" << realWidth << " realHeight=" << realHeight);

    m_coordinates.clear();
    m_timeToXCoordinateMappings.clear();

    m_coordinates.resize(modelData.size());

    m_xAxisStepValue = realWidth / modelData.size();

    for (auto i = 0; i < modelData.size(); i++)
    {
        auto xCoordinate = X_OFFSET + i * m_xAxisStepValue;
        m_timeToXCoordinateMappings[modelData.at(i).first] = xCoordinate;
        m_coordinates[i].setX(xCoordinate);
    }

    //==============================================================================

    std::vector<double> historicalValues;
    for (auto const& e : modelData) {
        historicalValues.push_back(e.second);
    }

    auto minMax = std::minmax_element(historicalValues.begin(), historicalValues.end());
    m_minRate = *(std::get<0>(minMax));
    m_maxRate = *(std::get<1>(minMax));

    DBG("minY=" << m_minRate << " maxY=" << m_maxRate);
    auto rangeY = m_maxRate - m_minRate;
    m_yAxisStepValue = realHeight / rangeY;
    DBG("yAxis step=" << m_yAxisStepValue);

    auto  i = 0;
    for (auto const& e : modelData)
    {
        m_coordinates[i].setY(rateToYCoordinate(e.second));
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

void HistoricalRatePlotComponent::modelUpdated(model::HistoricalRateModel*)
{
    repaint();
}

float HistoricalRatePlotComponent::rateToYCoordinate(float currentRate)
{
    auto height = getLocalBounds().getHeight();
    auto coordinate = height - Y_OFFSET - m_yAxisStepValue * (currentRate - m_minRate);
    return coordinate;
}

float HistoricalRatePlotComponent::yCoordinateToRate(float currentCoordinate)
{
    auto height = getLocalBounds().getHeight();
    auto rate = (height - currentCoordinate + Y_OFFSET) / m_yAxisStepValue + m_minRate;
    return rate;
}

}