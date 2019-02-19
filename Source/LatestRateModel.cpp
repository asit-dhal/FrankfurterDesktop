/*
  ==============================================================================

    LatestRateModel.cpp
    Created: 19 Feb 2019 11:55:41pm
    Author:  asitd

  ==============================================================================
*/

#include "LatestRateModel.h"
#include "Utility.h"

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
	auto response = m_req.getLastResponse().rates;
	m_baseCurrency = response.getBaseCurrency();
	m_time = response.getDateTime();
	m_currencySpotPrices = response.getSpotPrices();
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

JUCE_IMPLEMENT_SINGLETON(LatestRateModel);
