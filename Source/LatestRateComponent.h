/*
  ==============================================================================

    LatestRateComponent.h
    Created: 18 Feb 2019 2:18:25am
    Author:  asitd

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JsonRequest.h"
#include "LatestRateModel.h"

class LatestRateComponent :
    public Component,
    public Label::Listener,
    public Button::Listener,
    public LatestRateModel::Listener
{
public:

    class Listener
    {
    public:
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
    void labelTextChanged(Label* labelThatHasChanged) override;
    void buttonClicked(Button* button) override;

private:
    TableListBox m_table{ {}, nullptr };
    Font font{ 14.0f };
    std::vector<Listener*> m_listeners;
    Label m_filterText;
    TextButton m_refreshButton;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LatestRateComponent)
};
