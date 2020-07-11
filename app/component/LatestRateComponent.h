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
#include <helper/JsonRequest.h>
#include <model/LatestRateModel.h>

namespace component
{

class LatestRateComponent :
        public Component,
        public model::LatestRateModel::Listener
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

    void paint(Graphics&) override;
    void resized() override;
    void modelUpdated(model::LatestRateModel *) override;
    void addListener(Listener* listener);
    void informListener();

 private:
    TableListBox m_table{ {}, nullptr };
    Font font{ 14.0f };
    std::vector<Listener*> m_listeners;

 private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LatestRateComponent)
};

} // namespace component
