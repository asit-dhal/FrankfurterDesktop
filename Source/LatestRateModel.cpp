/*
  ==============================================================================

    LatestRateModel.cpp
    Created: 19 Feb 2019 11:55:41pm
    Author:  asitd

  ==============================================================================
*/

#include "LatestRateModel.h"
#include "Utility.h"

#include <boost/algorithm/string.hpp>

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
							std::vector<std::string> timeTokens;
							boost::algorithm::split(timeTokens, date, boost::is_any_of("-"));
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



JUCE_IMPLEMENT_SINGLETON(LatestRateModel);
