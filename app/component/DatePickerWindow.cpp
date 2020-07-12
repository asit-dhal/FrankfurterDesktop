#include "DatePickerWindow.h"

namespace component {

class DayButton : public Component
{
public:
    DayButton (DatePickerComponent& td)  : m_owner (td)
    {
        addAndMakeVisible (m_button);
    }

    void resized() override
    {
        m_button.setBounds(getLocalBounds());
    }

    void setRowAndColumn (int newRow, int newColumn, String data)
    {
        m_row = newRow;
        m_columnId = newColumn;
        m_button.setButtonText(data);
    }

private:
    DatePickerComponent& m_owner;
    TextButton m_button;
    int m_row, m_columnId;
};

DatePickerComponent::DatePickerComponent()
{
    addAndMakeVisible(&m_previousButton);
    addAndMakeVisible(&m_nextButton);
    addAndMakeVisible(&m_label);

    addAndMakeVisible(&m_dates);
    addAndMakeVisible(&m_okButton);
    addAndMakeVisible(&m_cancelButton);

    m_previousButton.setButtonText("<");
    m_nextButton.setButtonText(">");
    m_label.setText(m_dateTime.formatted("%B %Y"), dontSendNotification);
    m_label.setJustificationType(Justification::centred);
    m_okButton.setButtonText("Ok");
    m_cancelButton.setButtonText("Cancel");

    m_previousButton.onClick = [this] { gotoPreviousMonth(); };
    m_nextButton.onClick = [this] { gotoNextMonth(); };

    m_dates.getHeader().addColumn("Su", 1, 30);
    m_dates.getHeader().addColumn("Mo", 2, 30);
    m_dates.getHeader().addColumn("Tu", 3, 30);
    m_dates.getHeader().addColumn("Wd", 4, 30);
    m_dates.getHeader().addColumn("Th", 5, 30);
    m_dates.getHeader().addColumn("Fr", 6, 30);
    m_dates.getHeader().addColumn("Sa", 7, 30);

    setSize (400, 300);

    m_okButton.onClick = [this] { exitModalState(0); };
    m_cancelButton.onClick = [this] {
        getTopLevelComponent()->exitModalState(1);
        getTopLevelComponent()->setVisible(false);
    };

    m_dates.setModel(this);
    populateCalender();
}

DatePickerComponent::~DatePickerComponent()
{

}

void DatePickerComponent::paint(Graphics &)
{

}

void DatePickerComponent::resized()
{
    auto area = getLocalBounds();
    auto headerArea = area.removeFromTop(40);
    m_previousButton.setBounds(headerArea.removeFromLeft(50).reduced(0, 5));
    m_nextButton.setBounds(headerArea.removeFromRight(50).reduced(0, 5));
    m_label.setBounds(headerArea.reduced(5));

    auto buttonArea = area.removeFromBottom(40);
    m_okButton.setBounds(buttonArea.removeFromRight(100).reduced(5,5));
    m_cancelButton.setBounds(buttonArea.removeFromRight(100).reduced(5,5));

    m_dates.setBounds(area);
}

void DatePickerComponent::setDateTime(const Time dateTime)
{
    m_dateTime = dateTime;
}

void DatePickerComponent::populateCalender()
{
    m_calendar.clear();
    m_calendar.push_back({-1, -1, -1, -1, -1, -1, -1});

    Time tempTime{ m_dateTime.getYear(), m_dateTime.getMonth(), 1, 0, 0 };
    auto weekDayIndex = tempTime.getDayOfWeek();
    int weekIndex = 0;
    for(auto i = 1; i <= getLastdayOfMonth(); i++) {
        m_calendar[weekIndex][weekDayIndex] = i;
        if (weekDayIndex == 6) {
            weekDayIndex = 0;
            weekIndex++;
            m_calendar.push_back({-1, -1, -1, -1, -1, -1, -1});
        } else {
            weekDayIndex++;
        }
    }

    m_dates.updateContent();
}

int DatePickerComponent::getLastdayOfMonth()
{
    int lastDay = 0;
    if ((m_dateTime.getYear() % 4 == 0) && ((m_dateTime.getYear() % 100) != 0 || (m_dateTime.getYear() % 400) != 0)) {
        if (m_dateTime.getMonth() == 1) {
            lastDay = 29;
        }
        else {
            lastDay = 28;
        }
    } else {
        if (m_dateTime.getMonth() == 3 || m_dateTime.getMonth() == 5 || m_dateTime.getMonth() == 8 || m_dateTime.getMonth() == 10) {
            lastDay = 30;
        }
        else {
            lastDay = 31;
        }
    }

    return lastDay;
}

void DatePickerComponent::gotoPreviousMonth()
{
    if (m_dateTime.getMonth() == 0) {
        m_dateTime = Time(m_dateTime.getYear()-1, 11, 1, 0, 0);
    }
    else {
        m_dateTime = Time(m_dateTime.getYear(), m_dateTime.getMonth()-1, 1, 0, 0);
    }
    m_label.setText(m_dateTime.formatted("%B %Y"), dontSendNotification);
    populateCalender();
}

void DatePickerComponent::gotoNextMonth()
{
    if (m_dateTime.getMonth() == 11) {
        m_dateTime = Time(m_dateTime.getYear()+1, 0, 1, 0, 0);
    }
    else {
        m_dateTime = Time(m_dateTime.getYear(), m_dateTime.getMonth()+1, 1, 0, 0);
    }
    m_label.setText(m_dateTime.formatted("%B %Y"), dontSendNotification);
    populateCalender();
}

int DatePickerComponent::getNumRows()
{
    return static_cast<int>(m_calendar.size());
}

void DatePickerComponent::paintRowBackground(Graphics &g, int rowNumber, int, int, bool rowIsSelected)
{

}

void DatePickerComponent::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
//    std::ostringstream buffer;
//    if (rowNumber >= static_cast<int>(m_calendar.size())) {
//        return;
//    }
//    if (columnId > 7) {
//        return;
//    }
//    g.setFont(20.0f);
//    if (m_calendar[rowNumber][columnId-1] == -1) {
//        return;
//    }
//    std::string day = std::to_string(m_calendar[rowNumber][columnId-1]);
//    g.drawText(day, 2, 0, width - 4, height, Justification::centredLeft, true);
//    g.fillRect(width - 1, 0, 1, height);
}

int DatePickerComponent::getColumnAutoSizeWidth(int)
{
    return 40;
}

Component *DatePickerComponent::refreshComponentForCell(int rowNumber, int columnId, bool, Component *existingComponentToUpdate)
{
    if (rowNumber >= static_cast<int>(m_calendar.size())) {
        return nullptr;
    }
    if (columnId > 6) {
        return nullptr;
    }
    if (m_calendar[rowNumber][columnId-1] == -1) {
        if (auto* dayButton = static_cast<DayButton*> (existingComponentToUpdate)) {
            existingComponentToUpdate->setVisible(false);
        }
        return existingComponentToUpdate;
    }

    auto* dayButton = static_cast<DayButton*> (existingComponentToUpdate);
    if (dayButton == nullptr) {
        dayButton = new DayButton(*this);
        dayButton->setSize(20, 20);
    }

    dayButton->setRowAndColumn (rowNumber, columnId, std::to_string(m_calendar[rowNumber][columnId-1]));
    dayButton->setVisible(true);
    return dayButton;
}



}
