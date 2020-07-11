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

#include "JsonRequest.h"
#include "Utility.h"

JsonRequest::JsonRequest(String urlString) : ThreadPoolJob(urlString), url (urlString) {}

JsonRequest::Response JsonRequest::execute ()
{
    auto urlRequest = url.getChildURL (endpoint);
    bool hasFields = (fields.getProperties().size() > 0);
    if (hasFields) {
        MemoryOutputStream output;
        fields.writeAsJSON (output, 0, false, 20);
        urlRequest = urlRequest.withPOSTData (output.toString());
    }

    OptionalScopedPointer<InputStream> in (urlRequest.createInputStream (hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));

    response.result = checkInputStream (in);
    TRACE_CLS(JsonRequest, "status=" + std::to_string(response.status));
    if (response.result.failed()) {
        TRACE_CLS(JsonRequest, "Request failed");
        return response;
    }
    response.bodyAsString = in->readEntireStreamAsString();
    return response;
}


void JsonRequest::setGet (const String& remote)
{
    verb = "GET";
    this->endpoint = remote;
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
    if (! in) {
        return Result::fail ("HTTP request failed, check your internet connection");
    }
    return Result::ok();
}

String JsonRequest::stringPairArrayToHeaderString(StringPairArray stringPairArray)
{
    String result;
    for (auto key : stringPairArray.getAllKeys()) {
        result += key + ": " + stringPairArray.getValue(key, "") + "\n";
    }
    return result;
}

ThreadPoolJob::JobStatus JsonRequest::runJob()
{
    TRACE_CLS_LINE(JsonRequest);
    try {
        lastResponse = execute();
    }
    catch(const std::exception &e) {
        DBG("Exception: " << e.what());
    }
    signalJobShouldExit();
    return ThreadPoolJob::JobStatus::jobHasFinished;
}

const JsonRequest::Response JsonRequest::getLastResponse() const
{
    return lastResponse;
}
