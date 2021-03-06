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

namespace model
{

class LatestRateModel
        : public Thread::Listener
        , public AsyncUpdater
        , public TableListBoxModel
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
        virtual void modelUpdated(LatestRateModel* ) = 0;
    };

    ~LatestRateModel();

    void addListener(Listener* listenerToAdd);
    void removeListener(Listener* listenerToRemove);

    void exitSignalSent() override;
    void handleAsyncUpdate() override;
    Currency getBaseCurrency() const;
    void setBaseCurrency(Currency baseCurrency);
    const std::vector<Currency> getAllowedBaseCurrencies() const;
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
    void sendRequest();

 private:
    std::vector<std::pair<Currency, double>> m_currencySpotPrices;
    std::vector<Currency> m_allowedBaseCurrencies;
    Currency m_baseCurrency{ Currency::USD };
    Time m_time;
    JsonRequest m_req;
    ListenerList<Listener> m_listeners;

 public:
    JUCE_DECLARE_SINGLETON(LatestRateModel, true);
};

} // namespace model
