/*
  ==============================================================================

    LatestRateComponent.cpp
    Created: 18 Feb 2019 2:18:25am
    Author:  asitd

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LatestRateComponent.h"
#include "Utility.h"


//==============================================================================
LatestRateComponent::LatestRateComponent()
{
	addAndMakeVisible(&m_filterText);
	m_filterText.setFont(font);
	m_filterText.setText("Filter", dontSendNotification);
	m_filterText.setJustificationType(Justification::left);
	m_filterText.setEditable(true);
	m_filterText.attachToComponent(&m_table, false);
	m_filterText.showEditor();

	addAndMakeVisible(&m_refreshButton);
	m_refreshButton.setButtonText("Refresh");
	m_refreshButton.addListener(this);

	addAndMakeVisible(&m_table);
	m_table.setColour(ListBox::outlineColourId, Colours::grey);
	m_table.setOutlineThickness(1);

	m_table.getHeader().addColumn("Currency", 1, 50);
	m_table.getHeader().addColumn("Spot Price", 2, 50);


	m_filterText.addListener(this);

	LatestRateModel::getInstance()->addListener(this);
}

LatestRateComponent::~LatestRateComponent()
{
}

void LatestRateComponent::paint (Graphics&)
{
}

void LatestRateComponent::resized()
{
	auto area = getLocalBounds();
	auto topArea = area.removeFromTop(40);
	topArea.reduce(0, 10);
	m_refreshButton.setBounds(topArea.removeFromRight(100));
	m_filterText.setBounds(topArea);
	m_table.setBounds(area);
}

void LatestRateComponent::modelUpdated()
{
	m_baseCurrency = LatestRateModel::getInstance()->getBaseCurrency();
	m_time = LatestRateModel::getInstance()->getTimeOfLastUpdate();
	m_currencySpotPrices = LatestRateModel::getInstance()->getCurrencySpotPrices();
	m_table.updateContent();
	m_table.autoSizeAllColumns();
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
	if (rowNumber >= m_currencySpotPrices.size())
		return;
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
		e->statusChanged(String("new data arrived"));
	}
}

void LatestRateComponent::labelTextChanged(Label* labelThatHasChanged)
{

}


void LatestRateComponent::buttonClicked(Button* button)
{
	LatestRateModel::getInstance()->refresh();
}

void LatestRateComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{

}