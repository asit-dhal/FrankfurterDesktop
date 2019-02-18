/*
  ==============================================================================

    LatestRateComponent.cpp
    Created: 18 Feb 2019 2:18:25am
    Author:  asitd

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LatestRateComponent.h"

//==============================================================================
LatestRateComponent::LatestRateComponent() :
	m_threadPool(3), 
	m_req("http://www.ecb.europa.eu")
{
	addAndMakeVisible(&m_table);
	m_table.setColour(ListBox::outlineColourId, Colours::grey);
	m_table.setOutlineThickness(1);

	m_table.getHeader().addColumn("Currency", 1, 50);
	m_table.getHeader().addColumn("Spot Price", 2, 50);


	m_req.setGet("stats/eurofxref/eurofxref-daily.xml");
	m_req.addListener(this);
	m_threadPool.addJob(&m_req, false);
}

LatestRateComponent::~LatestRateComponent()
{
}

void LatestRateComponent::paint (Graphics&)
{
}

void LatestRateComponent::resized()
{
	m_table.setBounds(getLocalBounds());
}

void LatestRateComponent::exitSignalSent()
{
	triggerAsyncUpdate();
}

void LatestRateComponent::handleAsyncUpdate()
{
	auto response = m_req.getLastResponse().rates;
	m_baseCurrency = response.getBaseCurrency();
	m_time = response.getDateTime();
	m_currencySpotPrices = response.getSpotPrices();
	m_table.updateContent();
	m_table.autoSizeAllColumns();

	informListener();
}

int LatestRateComponent::getNumRows()
{
	return static_cast<int>(m_currencySpotPrices.size());
}

void LatestRateComponent::paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected)
{
	auto alternateColour = getLookAndFeel().findColour(ListBox::backgroundColourId)
		.interpolatedWith(getLookAndFeel().findColour(ListBox::textColourId), 0.03f);
	if (rowIsSelected)
		g.fillAll(Colours::lightblue);
	else if (rowNumber % 2)
		g.fillAll(alternateColour);
}

void LatestRateComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	g.setColour(rowIsSelected ? Colours::darkblue : getLookAndFeel().findColour(ListBox::textColourId));
	g.setFont(font);

	String text;
	if (columnId == 1)
	{
		text = String(describe(m_currencySpotPrices.at(rowNumber).first));
	}
	else
	{
		text = String(std::to_string(m_currencySpotPrices.at(rowNumber).second));
	}

	g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);

	g.setColour(getLookAndFeel().findColour(ListBox::backgroundColourId));
	g.fillRect(width - 1, 0, 1, height);
}

int LatestRateComponent::getColumnAutoSizeWidth(int columnId)
{
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
		widest = jmax(widest, font.getStringWidth(text));

	}
	return widest + 8;
}

Currency LatestRateComponent::getBaseCurrency() const
{
	return m_baseCurrency;
}

Time LatestRateComponent::getLatestRateTime() const
{
	return m_time;
}

void LatestRateComponent::addListener(Listener* listener)
{
	m_listeners.push_back(listener);
}

void LatestRateComponent::informListener()
{
	for (auto &e : m_listeners) {
		e->dataUpdated();
	}
}