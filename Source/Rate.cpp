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


#include "Rate.h"
#include "FlagIcons.h"

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
    if (str == std::string("EUR")) return Currency::EUR;
    else if (str == std::string("USD")) return Currency::USD;
    else if (str == std::string("JPY")) return Currency::JPY;
    else if (str == std::string("BGN")) return Currency::BGN;
    else if (str == std::string("CZK")) return Currency::CZK;
    else if (str == std::string("DKK")) return Currency::DKK;
    else if (str == std::string("GBP")) return Currency::GBP;
    else if (str == std::string("HUF")) return Currency::HUF;
    else if (str == std::string("PLN")) return Currency::PLN;
    else if (str == std::string("RON")) return Currency::RON;
    else if (str == std::string("SEK")) return Currency::SEK;
    else if (str == std::string("CHF")) return Currency::CHF;
    else if (str == std::string("ISK")) return Currency::ISK;
    else if (str == std::string("NOK")) return Currency::NOK;
    else if (str == std::string("HRK")) return Currency::HRK;
    else if (str == std::string("RUB")) return Currency::RUB;
    else if (str == std::string("TRY")) return Currency::TRY;
    else if (str == std::string("AUD")) return Currency::AUD;
    else if (str == std::string("BRL")) return Currency::BRL;
    else if (str == std::string("CAD")) return Currency::CAD;
    else if (str == std::string("CNY")) return Currency::CNY;
    else if (str == std::string("HKD")) return Currency::HKD;
    else if (str == std::string("IDR")) return Currency::IDR;
    else if (str == std::string("ILS")) return Currency::ILS;
    else if (str == std::string("INR")) return Currency::INR;
    else if (str == std::string("KRW")) return Currency::KRW;
    else if (str == std::string("MXN")) return Currency::MXN;
    else if (str == std::string("MYR")) return Currency::MYR;
    else if (str == std::string("NZD")) return Currency::NZD;
    else if (str == std::string("PHP")) return Currency::PHP;
    else if (str == std::string("SGD")) return Currency::SGD;
    else if (str == std::string("THB")) return Currency::THB;
    else return Currency::ZAR;
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

String toString(Currency currency)
{
    return String(toStdString(currency));
}

bool operator<(Currency c1, Currency c2)
{
    return static_cast<std::underlying_type_t<Currency>>(c1) < static_cast<std::underlying_type_t<Currency>>(c2);
}

Image getIconForCurrency(Currency c)
{
    switch (c) {
    case Currency::EUR: return ImageCache::getFromMemory(FlagIcons::EUR_png, FlagIcons::EUR_pngSize);
    case Currency::USD: return ImageCache::getFromMemory(FlagIcons::USD_png, FlagIcons::USD_pngSize);
    case Currency::JPY: return ImageCache::getFromMemory(FlagIcons::JPY_png, FlagIcons::JPY_pngSize);
    case Currency::BGN: return ImageCache::getFromMemory(FlagIcons::BGN_png, FlagIcons::BGN_pngSize);
    case Currency::CZK: return ImageCache::getFromMemory(FlagIcons::CZK_png, FlagIcons::CZK_pngSize);
    case Currency::DKK: return ImageCache::getFromMemory(FlagIcons::DKK_png, FlagIcons::DKK_pngSize);
    case Currency::GBP: return ImageCache::getFromMemory(FlagIcons::GBP_png, FlagIcons::GBP_pngSize);
    case Currency::HUF: return ImageCache::getFromMemory(FlagIcons::HUF_png, FlagIcons::HUF_pngSize);
    case Currency::PLN: return ImageCache::getFromMemory(FlagIcons::PLN_png, FlagIcons::PLN_pngSize);
    case Currency::RON: return ImageCache::getFromMemory(FlagIcons::RON_png, FlagIcons::RON_pngSize);
    case Currency::SEK: return ImageCache::getFromMemory(FlagIcons::SEK_png, FlagIcons::SEK_pngSize);
    case Currency::CHF: return ImageCache::getFromMemory(FlagIcons::CHF_png, FlagIcons::CHF_pngSize);
    case Currency::ISK: return ImageCache::getFromMemory(FlagIcons::ISK_png, FlagIcons::ISK_pngSize);
    case Currency::NOK: return ImageCache::getFromMemory(FlagIcons::NOK_png, FlagIcons::NOK_pngSize);
    case Currency::HRK: return ImageCache::getFromMemory(FlagIcons::HRK_png, FlagIcons::HRK_pngSize);
    case Currency::RUB: return ImageCache::getFromMemory(FlagIcons::RUB_png, FlagIcons::RUB_pngSize);
    case Currency::TRY: return ImageCache::getFromMemory(FlagIcons::TRY_png, FlagIcons::TRY_pngSize);
    case Currency::AUD: return ImageCache::getFromMemory(FlagIcons::AUD_png, FlagIcons::AUD_pngSize);
    case Currency::BRL: return ImageCache::getFromMemory(FlagIcons::BRL_png, FlagIcons::BRL_pngSize);
    case Currency::CAD: return ImageCache::getFromMemory(FlagIcons::CAD_png, FlagIcons::CAD_pngSize);
    case Currency::CNY: return ImageCache::getFromMemory(FlagIcons::CNY_png, FlagIcons::CNY_pngSize);
    case Currency::HKD: return ImageCache::getFromMemory(FlagIcons::HKD_png, FlagIcons::HKD_pngSize);
    case Currency::IDR: return ImageCache::getFromMemory(FlagIcons::IDR_png, FlagIcons::IDR_pngSize);
    case Currency::ILS: return ImageCache::getFromMemory(FlagIcons::ILS_png, FlagIcons::ILS_pngSize);
    case Currency::INR: return ImageCache::getFromMemory(FlagIcons::INR_png, FlagIcons::INR_pngSize);
    case Currency::KRW: return ImageCache::getFromMemory(FlagIcons::KRW_png, FlagIcons::KRW_pngSize);
    case Currency::MXN: return ImageCache::getFromMemory(FlagIcons::MXN_png, FlagIcons::MXN_pngSize);
    case Currency::MYR: return ImageCache::getFromMemory(FlagIcons::MYR_png, FlagIcons::MYR_pngSize);
    case Currency::NZD: return ImageCache::getFromMemory(FlagIcons::NZD_png, FlagIcons::NZD_pngSize);
    case Currency::PHP: return ImageCache::getFromMemory(FlagIcons::PHP_png, FlagIcons::PHP_pngSize);
    case Currency::SGD: return ImageCache::getFromMemory(FlagIcons::SGD_png, FlagIcons::SGD_pngSize);
    case Currency::THB: return ImageCache::getFromMemory(FlagIcons::THB_png, FlagIcons::THB_pngSize);
    case Currency::ZAR: return ImageCache::getFromMemory(FlagIcons::ZAR_png, FlagIcons::ZAR_pngSize);
    }
}

/*
String getCurrencySymbol(Currency c)
{
    switch (c)
    {
    case Currency::EUR: return String("€");
    case Currency::USD: return String("$");
    case Currency::JPY: return String("¥");
    case Currency::BGN: return String("лв");
    case Currency::CZK: return String("Kč");
    case Currency::DKK: return String("kr");
    case Currency::GBP: return String("£");
    case Currency::HUF: return String("Ft");
    case Currency::PLN: return String("zł");
    case Currency::RON: return String("L");
    case Currency::SEK: return String("kr");
    case Currency::CHF: return String("₣");
    case Currency::ISK: return String("Kr");
    case Currency::NOK: return String("kr");
    case Currency::HRK: return String("Kn");
    case Currency::RUB: return String("р.");
    case Currency::TRY: return String("₤");
    case Currency::AUD: return String("$");
    case Currency::BRL: return String("R$");
    case Currency::CAD: return String("$");
    case Currency::CNY: return String("¥");
    case Currency::HKD: return String("$");
    case Currency::IDR: return String("Rp");
    case Currency::ILS: return CharPointer_UTF8(u8"\xE2\x82\xAA");
    case Currency::INR: return String(u8"₹");
    case Currency::KRW: return String("₩");
    case Currency::MXN: return String("$");
    case Currency::MYR: return String("RM");
    case Currency::NZD: return String("$");
    case Currency::PHP: return String("₱");
    case Currency::SGD: return String("$");
    case Currency::THB: return String("฿");
    case Currency::ZAR: return String("R");
    default: return String("");
    }
}
*/
