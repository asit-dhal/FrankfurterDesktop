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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JsonRequest.h"
#include "LatestRateModel.h"

class LatestRateComponent :
    public Component,
    public LatestRateModel::Listener
{
public:

    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void dataUpdated() = 0;
        virtual void statusChanged(String message) = 0;
    };

    LatestRateComponent();
    ~LatestRateComponent();

    void paint (Graphics&) override;
    void resized() override;
    void modelUpdated() override;
    void addListener(Listener* listener);
    void informListener();

private:
    TableListBox m_table{ {}, nullptr };
    Font font{ 14.0f };
    std::vector<Listener*> m_listeners;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LatestRateComponent)
};
