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
#include "HistoricalRateComponent.h"

namespace component
{

HistoricalRateComponent::HistoricalRateComponent()
{
    addAndMakeVisible(&m_table);
    m_table.setColour(ListBox::outlineColourId, Colours::grey);
    m_table.setOutlineThickness(1);

    m_table.getHeader().addColumn("Date", 1, 50);
    m_table.getHeader().addColumn("Spot Price", 2, 50);

    auto modelInstance = model::HistoricalRateModel::getInstance();
    modelInstance->addListener(this);
    m_table.setModel(modelInstance);
 }

void HistoricalRateComponent::paint(Graphics&)
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
    if (m_table.getNumRows() > 0)
        m_table.selectRow(0);
}

} // namespace component