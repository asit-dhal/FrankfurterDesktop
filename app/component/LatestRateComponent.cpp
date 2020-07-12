/*
 * Copyright (c) 2018-2020 Asit Dhal.
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

#include "LatestRateComponent.h"
#include <helper/Utility.h>

namespace component {

LatestRateComponent::LatestRateComponent()
{
    m_baseCurrencyLabel.setText("Base Currency", dontSendNotification);
    addAndMakeVisible(&m_table);
    addAndMakeVisible(&m_baseCurrencyLabel);
    addAndMakeVisible(&m_baseCurrencyCombobox);
    m_table.setColour(ListBox::outlineColourId, Colours::grey);
    m_table.setOutlineThickness(1);

    for (auto const& e : model::LatestRateModel::getColumnNames()) {
        m_table.getHeader().addColumn(e.second, e.first, 50);
    }

    model::LatestRateModel::getInstance()->addListener(this);
    m_table.setModel(model::LatestRateModel::getInstance());

    for (auto const &e: model::LatestRateModel::getInstance()->getAllowedBaseCurrencies()) {
        m_baseCurrencyCombobox.addItem(describe(e), static_cast<int>(e));
    }
    m_baseCurrencyCombobox.onChange = [this]{ onBaseCurrencyChanged(); };

    m_baseCurrencyCombobox.setSelectedId(static_cast<int>(Currency::EUR));
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
    auto area = getLocalBounds();
    auto baseCurrencyArea = area.removeFromTop(30);
    m_baseCurrencyLabel.setBounds(baseCurrencyArea.removeFromLeft(100));
    m_baseCurrencyCombobox.setBounds(baseCurrencyArea.reduced(10, 0));
    m_table.setBounds(area.reduced(10));
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

void LatestRateComponent::onBaseCurrencyChanged()
{
    auto selectedCurrency = m_baseCurrencyCombobox.getSelectedId();
    model::LatestRateModel::getInstance()->setBaseCurrency(static_cast<Currency>(selectedCurrency));
}

} // namespace component
