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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "model/LatestRateModel.h"
#include "component/LatestRateComponent.h"
#include "component/HistoricalRateComponent.h"
#include "component/HistoricalRatePlotComponent.h"
#include <vector>
#include <tuple>

class MainComponent :
    public Component,
    public model::LatestRateModel::Listener,
    public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    //void handleAsyncUpdate() override;
    void modelUpdated(model::LatestRateModel*) override;
    //void statusChanged(String message) override;
    void timerCallback() override;

private:
    Label m_currencyLabel;
    Label m_dateLabel;
    component::LatestRateComponent m_latestRateComponent;
    component::HistoricalRateComponent m_historicalRateComponent;
    component::HistoricalRatePlotComponent m_historicalRatePlotComponent;
    Label m_statueLabel;
    Font font           { 14.0f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
