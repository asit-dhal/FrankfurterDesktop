/*
 * Copyright (c) 2018 Asit Dhal.
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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../model/HistoricalRateModel.h"

namespace component
{

    class HistoricalRatePlotComponent :
        public Component,
        public model::HistoricalRateModel::Listener
    {
    public:
        HistoricalRatePlotComponent();
        ~HistoricalRatePlotComponent();

        void paint(Graphics&) override;
        void resized() override;
        void modelUpdated() override;

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
        float m_minRate = 0.0;
        float m_maxRate = 0.0;

        Label m_statueLabel;
        std::vector<Listener*> m_listeners;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HistoricalRatePlotComponent)
    };

} // namespace component