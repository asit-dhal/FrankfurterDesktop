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

#include "HistoricalRateModel.h"
#include <helper/Utility.h>

#include <sstream>

namespace model {

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

void HistoricalRateModel::addListener(Listener* listenerToAdd)
{
    m_listeners.add(listenerToAdd);
}

void HistoricalRateModel::removeListener(Listener* listenerToRemove)
{
    jassert(m_listeners.contains(listenerToRemove));
    m_listeners.remove(listenerToRemove);
}

void HistoricalRateModel::informListener()
{
    m_listeners.call([this](Listener& l) { l.modelUpdated(this); });
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
    m_baseCurrency = fromStdString("EUR");

    if (auto xml = parseXML(response)) {
        if (xml->hasTagName("gesmes:Envelope")) {
            forEachXmlChildElement(*xml, envelope) {
                if (envelope->hasTagName("Cube")) {
                    forEachXmlChildElement(*envelope, cubeOuter) {
                        Time time;
                        std::map<Currency, double> rates;
                        if (cubeOuter->hasAttribute("time")) {
                            auto date = cubeOuter->getStringAttribute("time").toStdString();
                            std::vector<std::string> timeTokens = split(date, '-');
                            time = Time(std::stoi(timeTokens.at(0)), std::stoi(timeTokens.at(1)) - 1, std::stoi(timeTokens.at(2)), 0, 0);
                        }
                        if (cubeOuter->hasTagName("Cube")) {
                            forEachXmlChildElement(*cubeOuter, cubeWithTime){
                                if (cubeWithTime->hasTagName("Cube")) {
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
    if (rowIsSelected) {
        g.fillAll(Colours::lightblue);
    }
    else if (rowNumber % 2) {
        g.fillAll(alternateColour);
    }
}

void HistoricalRateModel::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    std::ostringstream buffer;
    if (rowNumber >= static_cast<int>(m_selectedCurrencyData.size()))
        return;
    g.setColour(rowIsSelected ? Colours::darkblue : TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::textColourId));
    g.setFont({ 14.0f });

    String text;
    if (columnId == 1) {
        text = m_selectedCurrencyData.at(rowNumber).first.toString(true, false);
    }
    else {
        buffer.str("");
        buffer.clear();
        buffer.precision(4);
        buffer << std::fixed << m_selectedCurrencyData.at(rowNumber).second;
        text = String(buffer.str());
    }

    g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);

    g.setColour(TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

int HistoricalRateModel::getColumnAutoSizeWidth(int columnId)
{
    int widest = 50;
    std::ostringstream buffer;
    for (auto i = getNumRows(); --i >= 0;) {
        String text;
        if (columnId == 1) {
            text = m_selectedCurrencyData.at(i).first.toString(true, false);
        }
        else {
            buffer.str("");
            buffer.clear();
            buffer.precision(4);
            buffer << std::fixed << m_selectedCurrencyData.at(i).second;
            text = String(buffer.str());
        }
        widest = jmax(widest, Font({ 14.0f }).getStringWidth(text));
    }
    return widest + 8;
}

void HistoricalRateModel::sortOrderChanged(int newSortColumnId, bool isForwards)
{
    auto column1Comparator = [&](const std::pair<Time, double>& lhs, const std::pair<Time, double>& rhs) {
        auto less = lhs.first < rhs.first;
        return isForwards ? less : !less;
    };

    /*auto column2Comparator = [&](const std::pair<Time, double>& lhs, const std::pair<Time, double>& rhs) {
        auto lhsVal = static_cast<int>(lhs.second * 10000);
        auto rhsVal = static_cast<int>(rhs.second * 10000);
        auto less = !(lhsVal > rhsVal);
        return isForwards ? less : !less;
    };*/



    if (newSortColumnId == 1) {
        std::sort(std::begin(m_selectedCurrencyData), std::end(m_selectedCurrencyData), column1Comparator);
    }
    /*else if (newSortColumnId == 2) {
        std::sort(std::begin(m_selectedCurrencyData), std::end(m_selectedCurrencyData), column2Comparator);
    }*/
}

} // namespace model
