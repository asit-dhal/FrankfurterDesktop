#pragma once

#include <JuceHeader.h>

#include <vector>

namespace component {

class DatePickerComponent
        : public Component
        , public juce::TableListBoxModel
{
public:
    DatePickerComponent();
    ~DatePickerComponent() override;
    void paint (Graphics&) override;
    void resized() override;
    void setDateTime(const Time dateTime);
    void* showCallback (void* userData);
    void populateCalender();
    int getLastdayOfMonth();
    void gotoPreviousMonth();
    void gotoNextMonth();
    void onEndSelection();
    void onDaySelected(int day);

    int getNumRows() override;
    void paintRowBackground (juce::Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override;
    void paintCell (juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    int getColumnAutoSizeWidth (int columnId) override;
    Component *refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,Component* existingComponentToUpdate) override;

    Time getSelectedDatetime() const;

private:
    TextButton m_previousButton;
    TextButton m_nextButton;
    Label m_label;
    TableListBox m_dates;
    TextButton m_okButton;
    TextButton m_cancelButton;
    Time m_dateTime;
    Time m_selectedDatetime;

    std::vector<std::vector<int>> m_calendar;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DatePickerComponent)
};

}
