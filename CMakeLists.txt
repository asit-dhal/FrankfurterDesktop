cmake_minimum_required(VERSION 3.12)

project(FrankfurterDesktop VERSION 0.0.2)

add_subdirectory(JUCE)
add_subdirectory(json)

juce_add_gui_app(FrankfurterDesktop
    BUNDLE_ID   asitdhal
    NEEDS_CURL  TRUE
)

juce_generate_juce_header(FrankfurterDesktop)

set(HELPER_SRCS
    app/helper/Utility.cpp
    app/helper/Currency.cpp
    app/helper/FlagIcons.cpp
    app/helper/JsonRequest.cpp
)

set(MODEL_SRCS
    app/model/HistoricalRateModel.cpp
    app/model/LatestRateModel.cpp
)

set(COMPONENT_SRCS
    app/component/HistoricalRateComponent.cpp
    app/component/HistoricalRatePlotComponent.cpp
    app/component/LatestRateComponent.cpp
)


target_sources(FrankfurterDesktop PRIVATE
    app/Main.cpp
    app/MainComponent.cpp
    ${HELPER_SRCS}
    ${MODEL_SRCS}
    ${COMPONENT_SRCS}
)

target_include_directories(FrankfurterDesktop PRIVATE
    app
)

target_compile_definitions(FrankfurterDesktop PRIVATE
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_USE_CURL=1
)

target_link_libraries(FrankfurterDesktop PRIVATE
    juce::juce_core
    juce::juce_graphics
    juce::juce_events
    juce::juce_gui_basics
    nlohmann_json::nlohmann_json
)
