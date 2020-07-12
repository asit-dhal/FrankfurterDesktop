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

#pragma once

#include "DatePickerWindow.h"
#include <JuceHeader.h>
#include <model/LatestRateModel.h>

namespace component {

class UserInputComponent
        : public Component
        , public model::LatestRateModel::Listener
{
 public:
    struct HistoricalDate {
        int year = -1;
        int month = -1;
        int day = -1;
    };

    UserInputComponent();
    ~UserInputComponent();

    void paint(Graphics&) override;
    void resized() override;
    void modelUpdated(model::LatestRateModel *) override;
    void addListener(Listener* listener);
    void informListener();
    void onBaseCurrencyChanged();
    static void* showCallback (void* userData);

 private:
    Label m_baseCurrencyLabel;
    ComboBox m_baseCurrencyCombobox;

    Label m_historicalDateRangeLabel;
    TextButton m_dateRangeTextButton;

    DatePickerComponent m_datePickerComponent;
    AlertWindow m_datePickerAlertWindow;

    Font font{ 14.0f };

    Currency m_baseCurrency;

    HistoricalDate m_startDate, m_endDate;

 private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UserInputComponent)
};

} // namespace component
