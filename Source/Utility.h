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