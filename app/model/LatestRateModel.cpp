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

#include "LatestRateModel.h"

#include "HistoricalRateModel.h"
#include <helper/FlagIcons.h>
#include <helper/Utility.h>

#include <nlohmann/json.hpp>
#include <sstream>


namespace model {

using json = nlohmann::json;

JUCE_IMPLEMENT_SINGLETON(LatestRateModel);

LatestRateModel::LatestRateModel()
    : m_req("https://api.frankfurter.app")
{
    m_allowedBaseCurrencies.push_back(Currency::EUR);
    m_allowedBaseCurrencies.push_back(Currency::USD);
    m_allowedBaseCurrencies.push_back(Currency::GBP);
    m_req.addListener(this);
}

void LatestRateModel::exitSignalSent()
{
    triggerAsyncUpdate();
}

void LatestRateModel::handleAsyncUpdate()
{
    parseResponse(m_req.getLastResponse().bodyAsString);
    informListener();
}

void LatestRateModel::addListener(Listener* listenerToAdd)
{
    m_listeners.add(listenerToAdd);
}

void LatestRateModel::removeListener(Listener* listenerToRemove)
{
    jassert(m_listeners.contains(listenerToRemove));
    m_listeners.remove(listenerToRemove);
}

void LatestRateModel::informListener()
{
    m_listeners.call([this](Listener& l) { l.modelUpdated(this); });
}

Currency LatestRateModel::getBaseCurrency() const
{
    return m_baseCurrency;
}

void LatestRateModel::setBaseCurrency(Currency baseCurrency)
{
    if (m_baseCurrency != baseCurrency) {
        m_baseCurrency = baseCurrency;
        sendRequest();
    }
}

const std::vector<Currency> LatestRateModel::getAllowedBaseCurrencies() const
{
    return m_allowedBaseCurrencies;
}

std::vector<std::pair<Currency, double>> LatestRateModel::getCurrencySpotPrices() const
{
    return m_currencySpotPrices;
}

Time LatestRateModel::getTimeOfLastUpdate() const
{
    return m_time;
}

void LatestRateModel::parseResponse(String response)
{
    std::map<Currency, double> rates;

    auto parsedResponse = json::parse(response.toStdString());
    for (json::iterator it = parsedResponse.begin(); it != parsedResponse.end(); ++it) {
        if (it.key() == "base") {
            std::string baseCurrency = it.value();
            if (m_baseCurrency != fromStdString(baseCurrency)) {
                DBG("Base currency from Frankfurter is different: " + baseCurrency);
            }
        }
        else if (it.key() == "date") {
            std::string dateToken = it.value();
            std::vector<std::string> timeTokens = split(dateToken, '-');
            m_time = Time(std::stoi(timeTokens.at(0)), std::stoi(timeTokens.at(1)) - 1,
                          std::stoi(timeTokens.at(2)), 0, 0);
        }
        else if (it.key() == "rates") {
            for (json::iterator rateItr = it.value().begin(); rateItr != it.value().end(); rateItr++) {
                rates[fromStdString(rateItr.key())] = rateItr.value();
            }
        }
    }

    m_currencySpotPrices.clear();
    for (auto const e : rates) {
        m_currencySpotPrices.emplace_back(e);
    }
}

void LatestRateModel::sendRequest()
{
    m_req.setGet("latest?from="+toString(m_baseCurrency));
    GlobalInstance::getInstance()->getThreadPool().addJob(&m_req, false);
}

int LatestRateModel::getNumRows()
{
    return static_cast<int>(m_currencySpotPrices.size());
}

void LatestRateModel::paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected)
{
    auto alternateColour = TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::backgroundColourId)
        .interpolatedWith(TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

void LatestRateModel::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    std::ostringstream buffer;
    if (rowNumber >= static_cast<int>(m_currencySpotPrices.size()))
        return;
    g.setColour(rowIsSelected ? Colours::darkblue : TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::textColourId));
    g.setFont(14.0f);

    String text;
    if (columnId == 1) {
        Image icon = getIconForCurrency(m_currencySpotPrices.at(rowNumber).first);
        g.drawImageWithin(icon, 0, 0, width, height, RectanglePlacement::RectanglePlacement::Flags::centred);
    }
    else if (columnId == 2) {
        text = String(describe(m_currencySpotPrices.at(rowNumber).first));
    }
    else {
        buffer.str("");
        buffer.clear();
        buffer.precision(4);
        buffer << std::fixed << m_currencySpotPrices.at(rowNumber).second;
        text = String(buffer.str());
    }

    g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);

    g.setColour(TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

int LatestRateModel::getColumnAutoSizeWidth(int columnId)
{
    int widest = 50;
    std::ostringstream buffer;

    for (auto i = getNumRows(); --i >= 0;) {
        String text;
        if (columnId == 1) {
            text = toString(m_currencySpotPrices.at(i).first);
        }
        else if (columnId == 2) {
            text = String(describe(m_currencySpotPrices.at(i).first));
        }
        else {
            buffer.str("");
            buffer.clear();
            buffer.precision(4);
            buffer << std::fixed << m_currencySpotPrices.at(i).second;
            text = String(buffer.str());
        }
        widest = jmax(widest, Font(20.0f).getStringWidth(text));

    }
    return widest + 8;
}

void LatestRateModel::selectedRowsChanged(int lastRowSelected)
{
    if (lastRowSelected < getNumRows()) {
        auto currency = m_currencySpotPrices.at(lastRowSelected).first;
        HistoricalRateModel::getInstance()->setHistoricalRateByCurrency(currency);
    }
}

std::map<int, String> LatestRateModel::getColumnNames()
{
    std::map<int, String> cols;
    cols.insert({ static_cast<int>(Column::eCountry), "Country" });
    cols.insert({ static_cast<int>(Column::eCurrencyName), "Currency Name" });
    cols.insert({ static_cast<int>(Column::eSpotPrice), "Spot Price" });
    return cols;
}

LatestRateModel::~LatestRateModel()
{
    clearSingletonInstance();
}

void LatestRateModel::sortOrderChanged(int newSortColumnId, bool isForwards)
{
    auto column1Comparator = [&](const std::pair<Currency, double>& lhs, const std::pair<Currency, double>& rhs) {
        auto less = toStdString(lhs.first) < toStdString(rhs.first);
        return isForwards ? less : !less;
    };

    auto column2Comparator = [&](const std::pair<Currency, double>& lhs, const std::pair<Currency, double>& rhs) {
        auto less = describe(lhs.first) < describe(rhs.first);
        return isForwards ? less : !less;
    };

    auto column3Comparator = [&](const std::pair<Currency, double>& lhs, const std::pair<Currency, double>& rhs) {
        auto less = lhs.second < rhs.second;
        return isForwards ? less : !less;
    };

    if (newSortColumnId == 1) {
        std::sort(std::begin(m_currencySpotPrices), std::end(m_currencySpotPrices), column1Comparator);
    }
    else if (newSortColumnId == 2) {
        std::sort(std::begin(m_currencySpotPrices), std::end(m_currencySpotPrices), column2Comparator);
    }
    else if (newSortColumnId == 3) {
        std::sort(std::begin(m_currencySpotPrices), std::end(m_currencySpotPrices), column3Comparator);
    }
}

} // namespace model
