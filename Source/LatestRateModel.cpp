/*
  ==============================================================================

    LatestRateModel.cpp
    Created: 19 Feb 2019 11:55:41pm
    Author:  asitd

  ==============================================================================
*/

#include "LatestRateModel.h"
#include "HistoricalRateModel.h"
#include "FlagIcons.h"
#include "Utility.h"

JUCE_IMPLEMENT_SINGLETON(LatestRateModel);

LatestRateModel::LatestRateModel() :
    m_req("http://www.ecb.europa.eu")
{
    m_req.setGet("stats/eurofxref/eurofxref-daily.xml");
    m_req.addListener(this);
    GlobalInstance::getInstance()->getThreadPool().addJob(&m_req, false);
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

void LatestRateModel::addListener(Listener* listener)
{
    m_listeners.push_back(listener);
}

void LatestRateModel::informListener()
{
    for (auto &e : m_listeners) {
        e->modelUpdated();
    }
}

Currency LatestRateModel::getBaseCurrency() const
{
    return m_baseCurrency;
}
std::vector<std::pair<Currency, double>> LatestRateModel::getCurrencySpotPrices() const
{
    return m_currencySpotPrices;
}

Time LatestRateModel::getTimeOfLastUpdate() const
{
    return m_time;
}

void LatestRateModel::refresh()
{
    m_req.setGet("stats/eurofxref/eurofxref-daily.xml");
    GlobalInstance::getInstance()->getThreadPool().addJob(&m_req, false);
}

void LatestRateModel::parseResponse(String response)
{
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
                        if (cubeOuter->hasAttribute("time"))
                        {
                            auto date = cubeOuter->getStringAttribute("time").toStdString();
                            std::vector<std::string> timeTokens = split(date, '-');
                            //boost::algorithm::split(timeTokens, date, boost::is_any_of("-"));
                            m_time = Time(std::stoi(timeTokens.at(0)), std::stoi(timeTokens.at(1)) - 1, std::stoi(timeTokens.at(2)), 0, 0);
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
                    }
                }
            }
        }
    }

    m_currencySpotPrices.clear();
    for (auto const e : rates)
    {
        m_currencySpotPrices.emplace_back(e);
    }
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
    if (rowNumber >= m_currencySpotPrices.size())
        return;
    g.setColour(rowIsSelected ? Colours::darkblue : TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::textColourId));
    g.setFont({ 14.0f });

    String text;
    if (columnId == 1) {
        Image icon = getIconForCurrency(m_currencySpotPrices.at(rowNumber).first);
        g.drawImageWithin(icon, 0, 0, width, height, RectanglePlacement::RectanglePlacement::Flags::centred);
    }
    else if (columnId == 2) {
        text = String(describe(m_currencySpotPrices.at(rowNumber).first));
    }
    else {
        text = String(std::to_string(m_currencySpotPrices.at(rowNumber).second));
    }

    g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);

    g.setColour(TopLevelWindow::getActiveTopLevelWindow()->getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

int LatestRateModel::getColumnAutoSizeWidth(int columnId)
{
    int widest = 50;
    for (auto i = getNumRows(); --i >= 0;) {
        String text;
        if (columnId == 1) {
            text = toString(m_currencySpotPrices.at(i).first);
        }
        else if (columnId == 2) {
            text = String(describe(m_currencySpotPrices.at(i).first));
        }
        else {
            text = String(std::to_string(m_currencySpotPrices.at(i).second));
        }
        widest = jmax(widest, Font({ 20.0f }).getStringWidth(text));

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
