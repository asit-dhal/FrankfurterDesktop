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
	public TableListBoxModel,
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
	int getNumRows() override;
	void paintRowBackground(Graphics& g, int rowNumber, int, int, bool rowIsSelected) override;
	void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	int getColumnAutoSizeWidth(int columnId) override;
	Currency getBaseCurrency() const;
	Time getLatestRateTime() const;
	void addListener(Listener* listener);
	void informListener();

	void labelTextChanged(Label* labelThatHasChanged) override;
	void buttonClicked(Button* button) override;
	void sortOrderChanged(int newSortColumnId, bool isForwards) override;

private:
	TableListBox m_table{ {}, this };
	std::vector<std::pair<Currency, double>> m_currencySpotPrices;
	Font font{ 14.0f };
	Currency m_baseCurrency;
	Time m_time;
	std::vector<Listener*> m_listeners;
	Label m_filterText;
	TextButton m_refreshButton;

 
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LatestRateComponent)
};
