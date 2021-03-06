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

#pragma once

#include <JuceHeader.h>
#include <map>
#include <string>
#include <vector>
#include <chrono>

enum class Currency
{
    EUR = 1,
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

String toString(Currency currency);

bool operator<(Currency c1, Currency c2);

Image getIconForCurrency(Currency c);

/*
String getCurrencySymbol(Currency c);
*/
