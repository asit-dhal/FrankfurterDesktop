/*
  ==============================================================================

    HistoricalRateModel.cpp
    Created: 20 Feb 2019 2:09:29am
    Author:  asitd

  ==============================================================================
*/

#include "HistoricalRateModel.h"
#include "Utility.h"

#include <boost/algorithm/string.hpp>

JUCE_IMPLEMENT_SINGLETON(HistoricalRateModel);

HistoricalRateModel::HistoricalRateModel() :
    m_req("http://www.ecb.europa.eu")
{
    m_selectedCurrency = Currency::INR;
    m_req.setGet("stats/eurofxref/eurofxref-hist-90d.xml");
    m_req.addListener(this);
    GlobalInstance::getInstance()->getThreadPool().addJob(&m_req, false);
}

void HistoricalRateModel::exitSignalSent()
{
    triggerAsyncUpdate();
}

void HistoricalRateModel::addListener(Listener* listener)
{
    m_listeners.push_back(listener);
}

void HistoricalRateModel::informListener()
{
    for (auto &e : m_listeners) {
        e->modelUpdated();
    }

}

void HistoricalRateModel::handleAsyncUpdate()
{
    parseResponse(m_req.getLastResponse().bodyAsString);
    setHistoricalRateByCurrency(m_selectedCurrency);
    informListener();
}

void HistoricalRateModel::parseResponse(String response)
{
    m_historicalRates.clear();
    std::map<Currency, double> rates;
    m_baseCurrency = fromStdString("EUR");

    if (auto xml = parseXML(response))
    {
        if (xml->hasTagName("gesmes:Envelope"))
        {
            forEachXmlChildElement(*xml, envelope)
            {
                if (envelope->hasTagName("Cube"))
                {
                    forEachXmlChildElement(*envelope, cubeOuter)
                    {
                        Time time;
                        std::map<Currency, double> rates;
                        if (cubeOuter->hasAttribute("time"))
                        {
                            auto date = cubeOuter->getStringAttribute("time").toStdString();
                            std::vector<std::string> timeTokens;
                            boost::algorithm::split(timeTokens, date, boost::is_any_of("-"));
                            time = Time(std::stoi(timeTokens.at(0)), std::stoi(timeTokens.at(1)) - 1, std::stoi(timeTokens.at(2)), 0, 0);
                        }
                        if (cubeOuter->hasTagName("Cube"))
                        {
                            forEachXmlChildElement(*cubeOuter, cubeWithTime)
                            {
                                if (cubeWithTime->hasTagName("Cube"))
                                {
                                    auto currency = cubeWithTime->getStringAttribute("currency");
                                    auto value = cubeWithTime->getDoubleAttribute("rate");
                                    rates[fromStdString(currency.toStdString())] = value;
                                }
                            }
                        }

                        m_historicalRates[time] = rates;
                    }
                }
            }
        }
    }
}

void HistoricalRateModel::setHistoricalRateByCurrency(const Currency& currency)
{
    m_selectedCurrencyData.clear();

    auto i = 0;
    for (auto e : m_historicalRates) {
        auto itr = e.second.find(currency);
        if (itr != e.second.end()) {
            i++;
            m_selectedCurrencyData.push_back(std::make_pair(e.first, itr->second));
        }
    }

    DBG("Selected Currency: " << toStdString(currency));

    informListener();
}

std::vector<std::pair<Time, double>> HistoricalRateModel::getHistoricalRates() const
{
    return m_selectedCurrencyData;
}

int HistoricalRateModel::getNumRows()
{
    return static_cast<int>(m_selectedCurrencyData.size());
}

void HistoricalRateModel::paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected)
{
    auto alternateColour = TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::backgroundColourId)
        .interpolatedWith(TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void HistoricalRateModel::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (rowNumber >= m_selectedCurrencyData.size())
        return;
    g.setColour(rowIsSelected ? Colours::darkblue : TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::textColourId));
    g.setFont({ 14.0f });

    String text;
    if (columnId == 1)
    {
        text = m_selectedCurrencyData.at(rowNumber).first.toString(true, false);
    }
    else
    {
        text = String(std::to_string(m_selectedCurrencyData.at(rowNumber).second));
    }

    g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);

    g.setColour(TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

int HistoricalRateModel::getColumnAutoSizeWidth(int columnId)
{
    int widest = 50;
    for (auto i = getNumRows(); --i >= 0;)
    {
        String text;
        if (columnId == 1)
        {
            text = m_selectedCurrencyData.at(i).first.toString(true, false);
        }
        else
        {
            text = String(std::to_string(m_selectedCurrencyData.at(i).second));
        }
        widest = jmax(widest, Font({ 14.0f }).getStringWidth(text));

    }
    return widest + 8;
}
