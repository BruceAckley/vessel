cmake_minimum_required(VERSION 3.22)

project(Vessel VERSION 0.1.0)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/Vessel")

add_compile_definitions(JUCE_COMPANY_NAME="BlueOrangePurple")
add_compile_definitions(JUCE_PRODUCT_NAME="Vessel")
add_compile_definitions(JUCE_PRODUCT_VERSION="0.1.0")

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME BlueOrangePurple
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    PLUGIN_MANUFACTURER_CODE IBOP
    PLUGIN_CODE VESL
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Vessel"
    NEEDS_WEBVIEW2 TRUE
)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/MidiProcessor.cpp
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/Chord.cpp
        database/sqlite3.c
        database/DatabaseManager.cpp
        ${INCLUDE_DIR}/ParameterIDs.h
        ${INCLUDE_DIR}/MidiProcessor.h
        ${INCLUDE_DIR}/PluginEditor.h
        ${INCLUDE_DIR}/PluginProcessor.h
        ${INCLUDE_DIR}/sqlite3.h
        ${INCLUDE_DIR}/DatabaseManager.h
        ${INCLUDE_DIR}/Chord.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/config
        ${CMAKE_CURRENT_SOURCE_DIR}/database
)

# Links to all necessary dependencies. The present ones are recommended by JUCE.
# If you use one of the additional modules, like the DSP module, you need to specify it here.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_gui_extra
        juce::juce_core
        juce::juce_audio_basics
        juce::juce_audio_processors
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
)

# Enables all warnings and treats warnings as errors.
# This needs to be set up only for your projects, not 3rd party
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /Wall /WX)
    # Silences some deprecation warnings that (hopefully) will be fixed in a future release of JUCE.
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
