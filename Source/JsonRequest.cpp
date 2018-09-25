/*
  ==============================================================================

    JsonRequest.cpp
    Created: 23 Sep 2018 9:00:24pm
    Author:  asit

  ==============================================================================
*/

#include "JsonRequest.h"
#include "Rate.h"

JsonRequest::JsonRequest(String urlString) : ThreadPoolJob(urlString), url (urlString) {}

JsonRequest::Response JsonRequest::execute ()
{
    auto urlRequest = url.getChildURL (endpoint);
    bool hasFields = (fields.getProperties().size() > 0);
    if (hasFields)
    {
        MemoryOutputStream output;

        fields.writeAsJSON (output, 0, false, 20);
        urlRequest = urlRequest.withPOSTData (output.toString());
    }
        
    ScopedPointer<InputStream> in (urlRequest.createInputStream (hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
        
    response.result = checkInputStream (in);
    if (response.result.failed())
    {
        Logger::outputDebugString("Request failed");
        return response;
    }

    response.bodyAsString = in->readEntireStreamAsString();
    

    return response;
}


void JsonRequest::setGet (const String& endpoint)
{
    verb = "GET";
    this->endpoint = endpoint;    
}

void JsonRequest::setField (const String& name, const var& value)
{
    this->fields.setProperty(name, value);
}

const URL& JsonRequest::getURL() const
{
    return url;
}
    
const String& JsonRequest::getBodyAsString() const
{
    return bodyAsString;
}

Result JsonRequest::checkInputStream (InputStream* in)
{
    if (! in) return Result::fail ("HTTP request failed, check your internet connection");
    return Result::ok();
}
    
String JsonRequest::stringPairArrayToHeaderString(StringPairArray stringPairArray)
{
    String result;
    for (auto key : stringPairArray.getAllKeys())
    {
        result += key + ": " + stringPairArray.getValue(key, "") + "\n";
    }
    return result;
}

ThreadPoolJob::JobStatus JsonRequest::runJob()
{
    try
    {
        lastResponse = execute();
        lastResponse.rates.parseFromString(response.bodyAsString.toStdString());
    }
    catch(const std::exception &e)
    {
        Logger::outputDebugString("Exception: " + String(e.what()));
    }
    signalJobShouldExit();
}

const JsonRequest::Response JsonRequest::getLastResponse() const
{
    return lastResponse;
}