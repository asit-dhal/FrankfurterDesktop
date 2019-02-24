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

    addAndMakeVisible(&m_table);
    m_table.setColour(ListBox::outlineColourId, Colours::grey);
    m_table.setOutlineThickness(1);

    for (auto const& e : LatestRateModel::getColumnNames())
    {
        m_table.getHeader().addColumn(e.second, e.first, 50);
    }

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
    m_table.setBounds(getLocalBounds());
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