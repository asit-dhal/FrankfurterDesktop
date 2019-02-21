/*
  ==============================================================================

    HistoricalRateModel.h
    Created: 20 Feb 2019 2:09:29am
    Author:  asitd

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Rate.h"
#include "JsonRequest.h"

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

    void setHistoricalRateByCurrency(const Currency& currency);


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
