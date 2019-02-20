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

    JsonRequest.h
    Created: 23 Sep 2018 9:00:24pm
    Author:  asit

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class JsonRequest : public ThreadPoolJob
{
public:
    
    JsonRequest (String urlString);
    JsonRequest ():ThreadPoolJob("no-name") {}
    
    struct Response
    {
        Result result;
        StringPairArray headers;
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
