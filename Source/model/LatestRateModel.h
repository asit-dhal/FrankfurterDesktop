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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Currency.h"
#include "../JsonRequest.h"

namespace model
{

    class LatestRateModel :
        public Thread::Listener,
        public AsyncUpdater,
        public TableListBoxModel
    {
    public:
        enum class Column
        {
            eCountry = 1,
            eCurrencyName,
            eSpotPrice
        };

        static std::map<int, String> getColumnNames();

        class Listener
        {
        public:
            virtual ~Listener() = default;
            virtual void modelUpdated() = 0;
        };

        void exitSignalSent() override;
        void handleAsyncUpdate() override;
        void addListener(Listener* listener);
        Currency getBaseCurrency() const;
        std::vector<std::pair<Currency, double>> getCurrencySpotPrices() const;
        Time getTimeOfLastUpdate() const;

        // model behavior
        int getNumRows() override;
        void paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected) override;
        void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
        int getColumnAutoSizeWidth(int columnId) override;
        void selectedRowsChanged(int lastRowSelected) override;
        void sortOrderChanged(int newSortColumnId, bool isForwards) override;

    private:
        LatestRateModel();
        void informListener();
        void parseResponse(String response);

    private:
        std::vector<std::pair<Currency, double>> m_currencySpotPrices;
        Currency m_baseCurrency;
        Time m_time;
        JsonRequest m_req;
        std::vector<Listener*> m_listeners;

    public:
        JUCE_DECLARE_SINGLETON(LatestRateModel, false);
    };

} // namespace model