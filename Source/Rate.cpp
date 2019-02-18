/* 
 * This file is part of the CurrencyExchangeData distribution (https://github.com/asit-dhal/CurrencyExchangeData ).
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


/*
  ==============================================================================

    Currency.cpp
    Created: 23 Sep 2018 10:56:08pm
    Author:  asit

  ==============================================================================
*/

#include "Rate.h"
#include <boost/algorithm/string.hpp>


std::string describe(Currency currency)
{
    switch(currency)
    {
    case Currency::EUR: return std::string("Euro");
    case Currency::USD: return std::string("US dollar");
    case Currency::JPY: return std::string("Japanese yen");
    case Currency::BGN: return std::string("Bulgarian lev");
    case Currency::CZK: return std::string("Czech koruna");
    case Currency::DKK: return std::string("Danish krone");
    case Currency::GBP: return std::string("Pound sterling");
    case Currency::HUF: return std::string("Hungarian forint");
    case Currency::PLN: return std::string("Polish zloty");
    case Currency::RON: return std::string("Romanian leu");
    case Currency::SEK: return std::string("Swedish krona");
    case Currency::CHF: return std::string("Swiss franc");
    case Currency::ISK: return std::string("Icelandic krona");
    case Currency::NOK: return std::string("Norwegian krone");
    case Currency::HRK: return std::string("Croatian kuna");
    case Currency::RUB: return std::string("Russian rouble");
    case Currency::TRY: return std::string("Turkish lira");
    case Currency::AUD: return std::string("Australian dollar");
    case Currency::BRL: return std::string("Brazilian real");
    case Currency::CAD: return std::string("Canadian dollar");
    case Currency::CNY: return std::string("Chinese yuan renminbi");
    case Currency::HKD: return std::string("Hong Kong dollar");
    case Currency::IDR: return std::string("Indonesian rupiah");
    case Currency::ILS: return std::string("Israeli shekel");
    case Currency::INR: return std::string("Indian rupee");
    case Currency::KRW: return std::string("South Korean won");
    case Currency::MXN: return std::string("Mexican peso");
    case Currency::MYR: return std::string("Malaysian ringgit");
    case Currency::NZD: return std::string("New Zealand dollar");
    case Currency::PHP: return std::string("Philippine piso");
    case Currency::SGD: return std::string("Singapore dollar");
    case Currency::THB: return std::string("Thai baht");
    case Currency::ZAR: return std::string("South African rand");
    default: return std::string("Unknown");
    }
}

Currency fromStdString(std::string str)
{
    if (boost::iequals(str, "EUR")) return Currency::EUR;
    else if (boost::iequals(str, "USD")) return Currency::USD;
    else if (boost::iequals(str, "JPY")) return Currency::JPY;
    else if (boost::iequals(str, "BGN")) return Currency::BGN;
    else if (boost::iequals(str, "CZK")) return Currency::CZK;
    else if (boost::iequals(str, "DKK")) return Currency::DKK;
    else if (boost::iequals(str, "GBP")) return Currency::GBP;
    else if (boost::iequals(str, "HUF")) return Currency::HUF;
    else if (boost::iequals(str, "PLN")) return Currency::PLN;
    else if (boost::iequals(str, "RON")) return Currency::RON;
    else if (boost::iequals(str, "SEK")) return Currency::SEK;
    else if (boost::iequals(str, "CHF")) return Currency::CHF;
    else if (boost::iequals(str, "ISK")) return Currency::ISK;
    else if (boost::iequals(str, "NOK")) return Currency::NOK;
    else if (boost::iequals(str, "HRK")) return Currency::HRK;
    else if (boost::iequals(str, "RUB")) return Currency::RUB;
    else if (boost::iequals(str, "TRY")) return Currency::TRY;
    else if (boost::iequals(str, "AUD")) return Currency::AUD;
    else if (boost::iequals(str, "BRL")) return Currency::BRL;
    else if (boost::iequals(str, "CAD")) return Currency::CAD;
    else if (boost::iequals(str, "CNY")) return Currency::CNY;
    else if (boost::iequals(str, "HKD")) return Currency::HKD;
    else if (boost::iequals(str, "IDR")) return Currency::IDR;
    else if (boost::iequals(str, "ILS")) return Currency::ILS;
    else if (boost::iequals(str, "INR")) return Currency::INR;
    else if (boost::iequals(str, "KRW")) return Currency::KRW;
    else if (boost::iequals(str, "MXN")) return Currency::MXN;
    else if (boost::iequals(str, "MYR")) return Currency::MYR;
    else if (boost::iequals(str, "NZD")) return Currency::NZD;
    else if (boost::iequals(str, "PHP")) return Currency::PHP;
    else if (boost::iequals(str, "SGD")) return Currency::SGD;
    else if (boost::iequals(str, "THB")) return Currency::THB;
    else if (boost::iequals(str, "ZAR")) return Currency::ZAR;
}

std::string toStdString(Currency currency)
{
    switch(currency)
    {
    case Currency::EUR: return std::string("EUR");
    case Currency::USD: return std::string("USD");
    case Currency::JPY: return std::string("JPY");
    case Currency::BGN: return std::string("BGN");
    case Currency::CZK: return std::string("CZK");
    case Currency::DKK: return std::string("DKK");
    case Currency::GBP: return std::string("GBP");
    case Currency::HUF: return std::string("HUF");
    case Currency::PLN: return std::string("PLN");
    case Currency::RON: return std::string("RON");
    case Currency::SEK: return std::string("SEK");
    case Currency::CHF: return std::string("CHF");
    case Currency::ISK: return std::string("ISK");
    case Currency::NOK: return std::string("NOK");
    case Currency::HRK: return std::string("HRK");
    case Currency::RUB: return std::string("RUB");
    case Currency::TRY: return std::string("TRY");
    case Currency::AUD: return std::string("AUD");
    case Currency::BRL: return std::string("BRL");
    case Currency::CAD: return std::string("CAD");
    case Currency::CNY: return std::string("CNY");
    case Currency::HKD: return std::string("HKD");
    case Currency::IDR: return std::string("IDR");
    case Currency::ILS: return std::string("ILS");
    case Currency::INR: return std::string("INR");
    case Currency::KRW: return std::string("KRW");
    case Currency::MXN: return std::string("MXN");
    case Currency::MYR: return std::string("MYR");
    case Currency::NZD: return std::string("NZD");
    case Currency::PHP: return std::string("PHP");
    case Currency::SGD: return std::string("SGD");
    case Currency::THB: return std::string("THB");
    case Currency::ZAR: return std::string("ZAR");
    default: return std::string("South African rand");
    }
}

Rate::Rate()
{
    m_allCurrencies.push_back(Currency::EUR);
    m_allCurrencies.push_back(Currency::USD);
    m_allCurrencies.push_back(Currency::JPY);
    m_allCurrencies.push_back(Currency::BGN);
    m_allCurrencies.push_back(Currency::CZK);
    m_allCurrencies.push_back(Currency::DKK);
    m_allCurrencies.push_back(Currency::GBP);
    m_allCurrencies.push_back(Currency::HUF);
    m_allCurrencies.push_back(Currency::PLN);
    m_allCurrencies.push_back(Currency::RON);
    m_allCurrencies.push_back(Currency::SEK);
    m_allCurrencies.push_back(Currency::CHF);
    m_allCurrencies.push_back(Currency::ISK);
    m_allCurrencies.push_back(Currency::NOK);
    m_allCurrencies.push_back(Currency::HRK);
    m_allCurrencies.push_back(Currency::RUB);
    m_allCurrencies.push_back(Currency::TRY);
    m_allCurrencies.push_back(Currency::AUD);
    m_allCurrencies.push_back(Currency::BRL);
    m_allCurrencies.push_back(Currency::CAD);
    m_allCurrencies.push_back(Currency::CNY);
    m_allCurrencies.push_back(Currency::HKD);
    m_allCurrencies.push_back(Currency::IDR);
    m_allCurrencies.push_back(Currency::ILS);
    m_allCurrencies.push_back(Currency::INR);
    m_allCurrencies.push_back(Currency::KRW);
    m_allCurrencies.push_back(Currency::MXN);
    m_allCurrencies.push_back(Currency::MYR);
    m_allCurrencies.push_back(Currency::NZD);
    m_allCurrencies.push_back(Currency::PHP);
    m_allCurrencies.push_back(Currency::SGD);
    m_allCurrencies.push_back(Currency::THB);
    m_allCurrencies.push_back(Currency::ZAR);
}

void Rate::parseFromString(std::string data)
{
	m_baseCurrency = fromStdString("EUR");
	if (auto xml = parseXML(String(data)))
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
							m_date = Time(std::stoi(timeTokens.at(0)), std::stoi(timeTokens.at(1))-1, std::stoi(timeTokens.at(2)), 0, 0); 
						}
						if (cubeOuter->hasTagName("Cube"))
						{
							forEachXmlChildElement(*cubeOuter, cubeWithTime)
							{
								if (cubeWithTime->hasTagName("Cube"))
								{
									auto currency = cubeWithTime->getStringAttribute("currency");
									auto value = cubeWithTime->getDoubleAttribute("rate");
									m_rates[fromStdString(currency.toStdString())] = value;
								}
							}
						}
					}
				}
			}
		}
	}
}

std::string Rate::stringify() const
{
    std::string str;
    str += "Base Currency: " + toStdString(m_baseCurrency) +  "| ";
    str += "Date: " + m_date.toString(true, false).toStdString() +  "| ";
    str += "Rates: [";
    for(auto const& ele:  m_rates)
    {
        str += toStdString(ele.first) + "=>" + std::to_string(ele.second) + ", ";
    }
    str += "]";
    return str;
}

Currency Rate::getBaseCurrency() const
{
    return m_baseCurrency;
}

Time Rate::getDateTime() const
{
    return m_date;
}

std::vector<std::pair<Currency, double>> Rate::getSpotPrices() const
{
    std::vector<std::pair<Currency, double>> ret;
    
    for(auto const e: m_rates)
    {
        ret.emplace_back(e);
    }
    return ret;
}

int Rate::getSpotPriceCount() const
{
    return m_rates.size();
}