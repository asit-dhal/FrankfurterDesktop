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

#include <JuceHeader.h>
#include <helper/Currency.h>
#include <helper/JsonRequest.h>

namespace model {

class HistoricalRateModel
        : public Thread::Listener
        , public AsyncUpdater
        , public TableListBoxModel
{
public:
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void modelUpdated(HistoricalRateModel*) = 0;
    };

    ~HistoricalRateModel();

    void addListener(Listener* listenerToAdd);
    void removeListener(Listener* listenerToRemove);

    void exitSignalSent() override;
    void handleAsyncUpdate() override;
    
    // model behavior
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    int getColumnAutoSizeWidth(int columnId) override;
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;

    void setHistoricalRateByCurrency(const Currency& currency);
    std::vector<std::pair<Time, double>> getHistoricalRates() const;
    void setBaseCurrency(Currency baseCurrency);



private:
    HistoricalRateModel();
    void informListener();
    void parseResponse(String response);
    void sendRequest();

private:
    struct TimeCompare
    {
      bool operator()(const Time &l, const Time &r) const
      {
        return l > r;
      }
    };
    std::map<Time, std::map<Currency, double>> m_historicalRates;
    Currency m_baseCurrency;
    Time m_startDate;
    Time m_endDate;
    JsonRequest m_req;
    ListenerList<Listener> m_listeners;
    Currency m_selectedCurrency;
    std::vector<std::pair<Time, double>> m_selectedCurrencyData;
public:
    JUCE_DECLARE_SINGLETON(HistoricalRateModel, true);
};

} // namespace model
