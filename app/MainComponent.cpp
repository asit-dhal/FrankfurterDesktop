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

#include "MainComponent.h"
#include <helper/Utility.h>
#include <utility>
#include <iostream>
#include <sstream>

MainComponent::MainComponent()
{
#if JUCE_MAC || JUCE_WINDOWS
    getLookAndFeel().setDefaultSansSerifTypefaceName("Arial Unicode MS");
#endif

    m_statueLabel.setJustificationType(Justification::left);
    m_statueLabel.setFont(font);

    addAndMakeVisible(m_latestRateComponent);
    addAndMakeVisible(m_historicalRateComponent);
    addAndMakeVisible(m_historicalRatePlotComponent);
    addAndMakeVisible(m_statueLabel);

    setSize (600, 400);

    model::LatestRateModel::getInstance()->addListener(this);

    TRACE_CLS_LINE(MainComponent);
}

MainComponent::~MainComponent()
{
    model::LatestRateModel::getInstance()->removeListener(this);
}

void MainComponent::paint (Graphics&)
{
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto windowWidth = area.getWidth();
    m_statueLabel.setBounds(area.removeFromBottom(20).reduced(5));
    auto latestRateComponentWith = (windowWidth * 3) / 10;
    auto historicalRateComponentWidth = (windowWidth * 1.5) / 10;

    m_latestRateComponent.setBounds(area.removeFromLeft(latestRateComponentWith).reduced(10));
    m_historicalRateComponent.setBounds(area.removeFromLeft(historicalRateComponentWidth).reduced(10));
    m_historicalRatePlotComponent.setBounds(area.reduced(10));
}


void MainComponent::modelUpdated(model::LatestRateModel*)
{
//    auto modelInstance = model::LatestRateModel::getInstance();
}

/*
void MainComponent::statusChanged(String message)
{
    m_statueLabel.setText(message, dontSendNotification);
    startTimer(3000);
}*/

void MainComponent::timerCallback()
{
    m_statueLabel.setText("", dontSendNotification);
}
