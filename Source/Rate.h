/*
  ==============================================================================

    Currency.h
    Created: 23 Sep 2018 10:56:08pm
    Author:  asit

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include <string>
#include <vector>
#include <chrono>

enum class Currency 
{
    EUR,
    USD, 
    JPY,
    BGN,
    CZK,
    DKK,
    GBP,
    HUF,
    PLN,
    RON,
    SEK,
    CHF,
    ISK,
    NOK,
    HRK,
    RUB,
    TRY,
    AUD,
    BRL,
    CAD,
    CNY,
    HKD,
    IDR,
    ILS,
    INR,
    KRW, 
    MXN, 
    MYR, 
    NZD, 
    PHP, 
    SGD, 
    THB, 
    ZAR
};

std::string describe(Currency currency);
Currency fromStdString(std::string str);
std::string toStdString(Currency currency);

class Rate
{
public:
    Rate();
    void parseFromString(std::string data);
    std::string stringify() const;
private:
    Currency m_baseCurrency;
    Time m_date;
    std::map<Currency, double> m_rates;
    std::vector<Currency> m_allCurrencies;
    
};