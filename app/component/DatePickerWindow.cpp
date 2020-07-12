#include "DatePickerWindow.h"

namespace component {

DatePickerComponent::DatePickerComponent()
{
    addAndMakeVisible(&m_dates);
    addAndMakeVisible(&m_okButton);
    addAndMakeVisible(&m_cancelButton);

    m_okButton.setButtonText("Ok");
    m_cancelButton.setButtonText("Cancel");

    m_dates.getHeader().addColumn("Su", 0, 30);
    m_dates.getHeader().addColumn("Mo", 1, 30);
    m_dates.getHeader().addColumn("Tu", 2, 30);
    m_dates.getHeader().addColumn("Wd", 3, 30);
    m_dates.getHeader().addColumn("Th", 4, 30);
    m_dates.getHeader().addColumn("Fr", 5, 30);
    m_dates.getHeader().addColumn("Sa", 6, 30);

    setSize (600, 400);

    m_okButton.onClick = [this] { exitModalState(0); };
    m_cancelButton.onClick = [this] { exitModalState(1); };
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
    auto buttonArea = area.removeFromBottom(40);
    m_okButton.setBounds(buttonArea.removeFromRight(100).reduced(5,5));
    m_cancelButton.setBounds(buttonArea.removeFromRight(100).reduced(5,5));
    m_dates.setBounds(area);
}


}
