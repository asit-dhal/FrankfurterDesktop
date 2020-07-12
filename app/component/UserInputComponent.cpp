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
    m_historicalStartDateLabel.setText("Historical Rate Start Date", dontSendNotification);
    m_historicalEndDateLabel.setText("Historical Rate End Date", dontSendNotification);
    m_dateRangeTextButton.setButtonText("date range");

    addAndMakeVisible(&m_baseCurrencyLabel);
    addAndMakeVisible(&m_baseCurrencyCombobox);

    addAndMakeVisible(&m_historicalStartDateLabel);
    addAndMakeVisible(&m_startDateYearCombobox);
    addAndMakeVisible(&m_startDateMonthCombobox);
    addAndMakeVisible(&m_startDateDayCombobox);

    addAndMakeVisible(&m_historicalEndDateLabel);
    addAndMakeVisible(&m_endDateYearCombobox);
    addAndMakeVisible(&m_endDateMonthCombobox);
    addAndMakeVisible(&m_endDateDayCombobox);

    addAndMakeVisible(&m_dateRangeTextButton);

    m_startDateYearCombobox.onChange = [this] { m_startDate.year = m_startDateYearCombobox.getSelectedId() + 1990; };
    m_startDateMonthCombobox.onChange = [this] { m_startDate.month = m_startDateMonthCombobox.getSelectedId(); };
    m_startDateDayCombobox.onChange = [this]{ m_startDate.day = m_startDateDayCombobox.getSelectedId(); };

    model::LatestRateModel::getInstance()->addListener(this);

    for (auto const &e: model::LatestRateModel::getInstance()->getAllowedBaseCurrencies()) {
        m_baseCurrencyCombobox.addItem(describe(e), static_cast<int>(e));
    }
    m_baseCurrencyCombobox.onChange = [this]{ onBaseCurrencyChanged(); };

    m_baseCurrencyCombobox.setSelectedId(static_cast<int>(Currency::EUR));

    populateDateRangeComboboxes();

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

    auto startDateArea = area.removeFromTop(40);
    m_historicalStartDateLabel.setBounds(startDateArea.removeFromLeft(110));
    m_startDateYearCombobox.setBounds(startDateArea.removeFromLeft(100).reduced(0, 5));
    m_startDateMonthCombobox.setBounds(startDateArea.removeFromLeft(80).reduced(0, 5));
    m_startDateDayCombobox.setBounds(startDateArea.removeFromLeft(80).reduced(0, 5));

//    auto endDateArea = area.removeFromTop(40);
//    m_historicalEndDateLabel.setBounds(endDateArea.removeFromLeft(110));
//    m_endDateYearCombobox.setBounds(endDateArea.removeFromLeft(100).reduced(0, 5));
//    m_endDateMonthCombobox.setBounds(endDateArea.removeFromLeft(80).reduced(0, 5));
//    m_endDateDayCombobox.setBounds(endDateArea.removeFromLeft(80).reduced(0, 5));
    m_dateRangeTextButton.setBounds(area);
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

void UserInputComponent::populateDateRangeComboboxes()
{
    Time currentTime = Time::getCurrentTime();

    // year
    for(auto i = 1991; i <= currentTime.getYear(); i++) {
        m_startDateYearCombobox.addItem(std::to_string(i), i%1990);
        m_endDateYearCombobox.addItem(std::to_string(i), i%1990);
    }
    m_startDateYearCombobox.setSelectedId(1, dontSendNotification);
    m_endDateYearCombobox.setSelectedId(currentTime.getYear()%1990, dontSendNotification);

    // month
    for(auto i = 1; i <= 12; i++) {
        m_startDateMonthCombobox.addItem(std::to_string(i), i);
        m_endDateMonthCombobox.addItem(std::to_string(i), i);
    }
    m_startDateMonthCombobox.setSelectedId(1, dontSendNotification);
    m_endDateMonthCombobox.setSelectedId(currentTime.getMonth(), dontSendNotification);

    // day
    for(auto i = 1; i <= getLastDayOfMonth(m_startDate); i++) {
        m_startDateDayCombobox.addItem(std::to_string(i), i);
    }
    m_startDateDayCombobox.setSelectedId(1, dontSendNotification);

    for(auto i = 1; i <= getLastDayOfMonth(m_endDate); i++) {
        m_endDateDayCombobox.addItem(std::to_string(i), i);
    }
    m_endDateDayCombobox.setSelectedId(currentTime.getDayOfMonth(), dontSendNotification);
}

int UserInputComponent::getLastDayOfMonth(const UserInputComponent::HistoricalDate &date)
{
    int lastDay = 0;
    if ((date.year % 4 == 0)
            && ((date.year % 100) != 0 || (date.year % 400) != 0)) {
        if (m_startDate.month == 2) {
            lastDay = 29;
        }
        else {
            lastDay = 28;
        }
    } else {
        if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
            lastDay = 30;
        }
        else {
            lastDay = 31;
        }
    }

    return lastDay;
}

void* UserInputComponent::showCallback (void* userData)
{
    static_cast<AlertWindow*>(userData)->enterModalState(true, nullptr);
    return nullptr;
}


} // namespace component
