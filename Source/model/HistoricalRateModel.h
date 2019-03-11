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
    class HistoricalRateModel :
        public Thread::Listener,
        public AsyncUpdater,
        public TableListBoxModel
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;
            virtual void modelUpdated() = 0;
        };

        void exitSignalSent() override;
        void handleAsyncUpdate() override;
        void addListener(Listener* listener);

        // model behavior
        int getNumRows() override;
        void paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected) override;
        void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
        int getColumnAutoSizeWidth(int columnId) override;
        void sortOrderChanged(int newSortColumnId, bool isForwards) override;

        void setHistoricalRateByCurrency(const Currency& currency);
        std::vector<std::pair<Time, double>> getHistoricalRates() const;

    private:
        HistoricalRateModel();
        void informListener();
        void parseResponse(String response);

    private:
        std::map<Time, std::map<Currency, double>> m_historicalRates;
        Currency m_baseCurrency;
        JsonRequest m_req;
        std::vector<Listener*> m_listeners;
        Currency m_selectedCurrency;
        std::vector<std::pair<Time, double>> m_selectedCurrencyData;
    public:
        JUCE_DECLARE_SINGLETON(HistoricalRateModel, false);
    };

} // namespace model