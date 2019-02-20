/*
  ==============================================================================

    HistoricalRateComponent.cpp
    Created: 20 Feb 2019 6:50:46pm
    Author:  asitd

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "HistoricalRateComponent.h"

//==============================================================================
HistoricalRateComponent::HistoricalRateComponent()
{
    addAndMakeVisible(&m_table);
    m_table.setColour(ListBox::outlineColourId, Colours::grey);
    m_table.setOutlineThickness(1);

    m_table.getHeader().addColumn("Date", 1, 50);
    m_table.getHeader().addColumn("Spot Price", 2, 50);

    auto modelInstance = HistoricalRateModel::getInstance();
    modelInstance->addListener(this);
    m_table.setModel(modelInstance);
}

HistoricalRateComponent::~HistoricalRateComponent()
{
}

void HistoricalRateComponent::paint (Graphics&)
{
}

void HistoricalRateComponent::resized()
{
    m_table.setBounds(getLocalBounds());
}

void HistoricalRateComponent::modelUpdated()
{
    m_table.updateContent();
    m_table.autoSizeAllColumns();
}