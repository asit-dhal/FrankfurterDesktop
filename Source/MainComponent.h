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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "LatestRateComponent.h"
#include <vector>
#include <tuple>

class MainComponent : 
	public Component, 
	public AsyncUpdater, 
	public LatestRateComponent::Listener,
	public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void handleAsyncUpdate() override;
	void dataUpdated() override;
	void statusChanged(String message) override;
	void timerCallback() override;

private:
    Label m_currencyLabel;
    Label m_dateLabel;   
	LatestRateComponent m_latestRateComponent;
	Label m_statueLabel;
    Font font           { 14.0f };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
