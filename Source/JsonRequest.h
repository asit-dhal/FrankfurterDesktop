/*
  ==============================================================================

    JsonRequest.h
    Created: 23 Sep 2018 9:00:24pm
    Author:  asit

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Rate.h"

class JsonRequest : public ThreadPoolJob
{
public:
    
    JsonRequest (String urlString);
    JsonRequest ():ThreadPoolJob("no-name") {}
    
    struct Response
    {
        Result result;
        StringPairArray headers;
        Rate rates;
        String bodyAsString;
        int status;
        
        Response() : result (Result::ok()), status (0) {}
    } response;

    ThreadPoolJob::JobStatus runJob() override;
    void setGet (const String& endpoint);
    void setField (const String& name, const var& value);
    const URL& getURL() const;
    const String& getBodyAsString() const;
    const Response getLastResponse() const;
    
private:
    URL url;
    StringPairArray headers;
    String verb;
    String endpoint;
    DynamicObject fields;
    String bodyAsString;
    Response lastResponse;

    JsonRequest::Response execute ();
    Result checkInputStream (InputStream* in);
    static String stringPairArrayToHeaderString(StringPairArray stringPairArray);
};
