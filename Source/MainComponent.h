#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JsonRequest.h"
#include "Rate.h"
#include <vector>
#include <tuple>

class MainComponent : public Component
                    , public TableListBoxModel
                    , public Thread::Listener
                    , public AsyncUpdater
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void exitSignalSent() override;
    void handleAsyncUpdate() override;
    
    int getNumRows() override;
    void paintRowBackground (Graphics& g, int rowNumber, int, int, bool rowIsSelected) override;
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool rowIsSelected) override;
    int getColumnAutoSizeWidth (int columnId) override;

private:
    ThreadPool m_threadPool;
    JsonRequest m_req;
    std::vector<std::pair<Currency, double>> m_currencySpotPrices;
    
    Label m_currencyLabel;
    Label m_dateLabel;
    
    TableListBox m_table { {}, this };
    
    Font font           { 14.0f };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
