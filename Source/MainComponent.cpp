/*
 * This file is part of the CurrencyExchangeData distribution (https://github.com/asit-dhal/CurrencyExchangeData ).
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

#include "MainComponent.h"
#include "Utility.h"
#include <utility>
#include <iostream>
#include <sstream>

MainComponent::MainComponent()
{
    m_currencyLabel.setJustificationType (Justification::centred);
    m_dateLabel.setJustificationType (Justification::centred);
    m_statueLabel.setJustificationType(Justification::left);

    m_currencyLabel.setFont (Font (16.0f, Font::bold));
    m_dateLabel.setFont (Font (16.0f, Font::bold));
    m_statueLabel.setFont(font);

    addAndMakeVisible(&m_currencyLabel);
    addAndMakeVisible(&m_dateLabel);
    addAndMakeVisible(&m_latestRateComponent);
    addAndMakeVisible(&m_historicalRateComponent);
    addAndMakeVisible(&m_statueLabel);

    setSize (600, 400);

    LatestRateModel::getInstance()->addListener(this);

    TRACE_CLS_LINE(MainComponent);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics&)
{
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto titleHeight = 30;
    auto windowWidth = area.getWidth();
    m_currencyLabel.setBounds(area.removeFromTop(titleHeight).reduced(5));
    m_dateLabel.setBounds(area.removeFromTop(titleHeight).reduced(5));
    m_statueLabel.setBounds(area.removeFromBottom(20).reduced(5));
    m_latestRateComponent.setBounds(area.removeFromLeft(windowWidth/2).reduced(10));
    m_historicalRateComponent.setBounds(area.reduced(10));
}


void MainComponent::modelUpdated()
{
    auto modelInstance = LatestRateModel::getInstance();
    auto baseCurrencyText = "Base Currency: " + String(describe(modelInstance->getBaseCurrency()));
    auto dateTimeText = "Foreign Exchange reference rates on " + modelInstance->getTimeOfLastUpdate().toString(true, false);
    m_currencyLabel.setText(baseCurrencyText, dontSendNotification);
    m_dateLabel.setText(dateTimeText, dontSendNotification);
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
