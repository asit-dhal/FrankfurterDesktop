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

    utility.h
    Created: 26 Sep 2018 1:21:41am
    Author:  asit

  ==============================================================================
*/

#pragma once

#define TRACE(msg) DBG(String("Time=") + String(std::to_string(Time::currentTimeMillis())) + " tid=" + String::toHexString ((int64)Thread::getCurrentThreadId()) + " " + __FUNCTION__ + ":" + String(__LINE__) + " " + msg)
#define TRACE_CLS(cls, msg) DBG(String("Time=") + String(std::to_string(Time::currentTimeMillis())) + " tid=" + String::toHexString ((int64)Thread::getCurrentThreadId()) + " " + String(#cls) + "::" + __FUNCTION__ + ":" +  String(__LINE__) + " " +  msg)
#define TRACE_LINE  DBG(String("Time=") + String(std::to_string(Time::currentTimeMillis())) + " tid=" + String::toHexString ((int64)Thread::getCurrentThreadId()) + " " + __FUNCTION__ + ":" + String(__LINE__))
#define TRACE_CLS_LINE(cls) DBG(String("Time=") + String(std::to_string(Time::currentTimeMillis())) + " tid=" + String::toHexString ((int64)Thread::getCurrentThreadId()) + " " + String(#cls) + "::" + __FUNCTION__ + ":" +  String(__LINE__))