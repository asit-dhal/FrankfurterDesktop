#pragma once

#include <JuceHeader.h>

namespace component {

class DatePickerComponent
        : public Component
{
public:
    DatePickerComponent();
    ~DatePickerComponent() override;
    void paint (Graphics&) override;
    void resized() override;
    void* showCallback (void* userData);

private:
    TableListBox m_dates;
    TextButton m_okButton;
    TextButton m_cancelButton;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DatePickerComponent)
};

}
