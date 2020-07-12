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

#include "UserInputComponent.h"
#include <model/HistoricalRateModel.h>
#include <helper/Utility.h>

namespace component {


UserInputComponent::UserInputComponent()
    : m_datePickerAlertWindow("", "", AlertWindow::NoIcon)
{
    m_baseCurrencyLabel.setText("Base Currency", dontSendNotification);
    m_historicalDateRangeLabel.setText("Historical Rate Date Range", dontSendNotification);
    m_dateRangeTextButton.setButtonText("date range");

    addAndMakeVisible(&m_baseCurrencyLabel);
    addAndMakeVisible(&m_baseCurrencyCombobox);
    addAndMakeVisible(&m_historicalDateRangeLabel);
    addAndMakeVisible(&m_dateRangeTextButton);

    model::LatestRateModel::getInstance()->addListener(this);

    for (auto const &e: model::LatestRateModel::getInstance()->getAllowedBaseCurrencies()) {
        m_baseCurrencyCombobox.addItem(describe(e), static_cast<int>(e));
    }
    m_baseCurrencyCombobox.onChange = [this]{ onBaseCurrencyChanged(); };

    m_baseCurrencyCombobox.setSelectedId(static_cast<int>(Currency::EUR));


    m_datePickerComponent.setDateTime(Time::getCurrentTime());
    m_datePickerAlertWindow.addCustomComponent(&m_datePickerComponent);

    m_dateRangeTextButton.onClick = [this] {
        MessageManager::getInstance()->callFunctionOnMessageThread (showCallback, (void*) (&m_datePickerAlertWindow));
    };
}

UserInputComponent::~UserInputComponent()
{
    model::LatestRateModel::getInstance()->removeListener(this);
}

void UserInputComponent::paint(Graphics&)
{
}

void UserInputComponent::resized()
{
    auto area = getLocalBounds();

    auto baseCurrencyArea = area.removeFromTop(40);
    m_baseCurrencyLabel.setBounds(baseCurrencyArea.removeFromLeft(110));
    m_baseCurrencyCombobox.setBounds(baseCurrencyArea.reduced(5));

    auto dateRangeArea = area.removeFromTop(40);
    m_historicalDateRangeLabel.setBounds(dateRangeArea.removeFromLeft(110));
    m_dateRangeTextButton.setBounds(dateRangeArea.removeFromLeft(100).reduced(0, 5));
}

void UserInputComponent::modelUpdated(model::LatestRateModel *p_latestRateModel)
{
    if (m_baseCurrency != p_latestRateModel->getBaseCurrency()) {
        m_baseCurrency = p_latestRateModel->getBaseCurrency();
        m_baseCurrencyCombobox.setSelectedId(static_cast<int>(m_baseCurrency), dontSendNotification);
    }
}

void UserInputComponent::onBaseCurrencyChanged()
{
    auto selectedCurrency = m_baseCurrencyCombobox.getSelectedId();
    model::LatestRateModel::getInstance()->setBaseCurrency(static_cast<Currency>(selectedCurrency));
    model::HistoricalRateModel::getInstance()->setBaseCurrency(static_cast<Currency>(selectedCurrency));
}

void* UserInputComponent::showCallback (void* userData)
{
    static_cast<AlertWindow*>(userData)->enterModalState(true, nullptr);
    return nullptr;
}


} // namespace component
