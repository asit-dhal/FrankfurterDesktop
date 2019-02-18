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
#include <json.hpp>
#include <iostream>
#include <sstream>

MainComponent::MainComponent(): m_threadPool(3)
                              , m_req("http://www.ecb.europa.eu")
{
    
    m_currencyLabel.setJustificationType (Justification::centred);
    m_dateLabel.setJustificationType (Justification::centred);
    
    m_currencyLabel.setFont (Font (16.0f, Font::bold));
    m_dateLabel.setFont (Font (16.0f, Font::bold));
    addAndMakeVisible(&m_currencyLabel);
    addAndMakeVisible(&m_dateLabel);
    
    addAndMakeVisible(&m_table);
    m_table.setColour(ListBox::outlineColourId, Colours::grey);
    m_table.setOutlineThickness(1);
    
    m_table.getHeader().addColumn("Currency", 1, 50);
    m_table.getHeader().addColumn("Spot Price", 2, 50);
    
    setSize (600, 400);
    
    m_req.setGet("stats/eurofxref/eurofxref-daily.xml");
    m_req.addListener(this);
    m_threadPool.addJob(&m_req, false);
    TRACE_CLS_LINE(MainComponent);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    
    auto titleHeight = 30;
    m_currencyLabel.setBounds(area.removeFromTop(titleHeight).reduced(5));
    m_dateLabel.setBounds(area.removeFromTop(titleHeight).reduced(5));

    m_table.setBounds(area.reduced(10));
}

void MainComponent::exitSignalSent()
{
    TRACE_CLS_LINE(MainComponent);
    triggerAsyncUpdate();
}

void MainComponent::handleAsyncUpdate()
{
    TRACE_CLS_LINE(MainComponent);
    auto response = m_req.getLastResponse().rates;
    TRACE_CLS(MainComponent, "Rates: " + String(response.stringify()));
    
    auto baseCurrencyText = "Base Currency: " + String(describe(response.getBaseCurrency()));
    auto dateTimeText = "Foreign Exchange reference rates on " +response.getDateTime().toString(true, false);
    m_currencyLabel.setText(baseCurrencyText, dontSendNotification);
    m_dateLabel.setText(dateTimeText, dontSendNotification);   
 
    m_currencySpotPrices = response.getSpotPrices();
    m_table.updateContent();
    m_table.autoSizeAllColumns();
}

int MainComponent::getNumRows()
{
    return m_currencySpotPrices.size();
}

void MainComponent::paintRowBackground (Graphics& g, int rowNumber, int, int, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour (ListBox::backgroundColourId)
                                               .interpolatedWith (getLookAndFeel().findColour (ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll (Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll (alternateColour);
}

void MainComponent::paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool rowIsSelected)
{
    TRACE_CLS(MainComponent, "rowNumber= " + std::to_string(rowNumber) + " columnId=" + std::to_string(columnId));
    g.setColour (rowIsSelected ? Colours::darkblue : getLookAndFeel().findColour (ListBox::textColourId));
    g.setFont (font);
    
    String text;
    if (columnId == 1)
    {
        text = String(describe(m_currencySpotPrices.at(rowNumber).first));
    }
    else
    {
        text = String(std::to_string(m_currencySpotPrices.at(rowNumber).second));
    }

    g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
    
    g.setColour (getLookAndFeel().findColour (ListBox::backgroundColourId));
    g.fillRect (width - 1, 0, 1, height);
}


int MainComponent::getColumnAutoSizeWidth (int columnId)
{
    TRACE_CLS(MainComponent, "columnId=" + std::to_string(columnId));
    int widest = 50;
    for (auto i = getNumRows(); --i >= 0;)
    {
        String text;
        if (columnId == 1)
        {
            text = String(describe(m_currencySpotPrices.at(i).first));
        }
        else
        {
            text = String(std::to_string(m_currencySpotPrices.at(i).second));
        }   
        widest = jmax (widest, font.getStringWidth (text));

    }
    return widest + 8;
}