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
	m_table.setModel(LatestRateModel::getInstance());
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
	m_table.updateContent();
	m_table.autoSizeAllColumns();
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
