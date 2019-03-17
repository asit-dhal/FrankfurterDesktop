/*
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

#include "../JuceLibraryCode/JuceHeader.h"
#include "LatestRateComponent.h"
#include "../Utility.h"

namespace component
{

LatestRateComponent::LatestRateComponent()
{
    addAndMakeVisible(&m_table);
    m_table.setColour(ListBox::outlineColourId, Colours::grey);
    m_table.setOutlineThickness(1);

    for (auto const& e : model::LatestRateModel::getColumnNames())
        m_table.getHeader().addColumn(e.second, e.first, 50);

    model::LatestRateModel::getInstance()->addListener(this);
    m_table.setModel(model::LatestRateModel::getInstance());
}

LatestRateComponent::~LatestRateComponent()
{
    model::LatestRateModel::getInstance()->removeListener(this);
}

void LatestRateComponent::paint(Graphics&)
{
}

void LatestRateComponent::resized()
{
    m_table.setBounds(getLocalBounds());
}

void LatestRateComponent::modelUpdated(model::LatestRateModel *)
{
    m_table.updateContent();
    m_table.autoSizeAllColumns();
    if (m_table.getNumRows() > 0)
        m_table.selectRow(0);
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

} // namespace component