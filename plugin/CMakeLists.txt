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

# Mark JUCE headers as system headers to suppress warnings in them
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${JUCE_MODULES_DIR})

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

# Folder where web UI data reside
set(UI_FILES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ui/dist")

# Copy JUCE frontend library to plugin UI files
file(COPY "${JUCE_MODULES_DIR}/juce_gui_extra/native/javascript/" DESTINATION "${UI_FILES_SOURCE_DIR}/js/juce/")

# Copy WebView UI files; does not allow hot reloading
get_target_property(PLUGIN_OUTPUT_DIR ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
set(UI_FILES_DEST_DIR "${PLUGIN_OUTPUT_DIR}/public")

# Puts UI files in place
if(NOT EXISTS ${UI_FILES_SOURCE_DIR})
    message(FATAL_ERROR "Source UI directory not found: ${UI_FILES_SOURCE_DIR}")
endif()
file(MAKE_DIRECTORY ${UI_FILES_DEST_DIR})
# add_custom_command(
#     TARGET ${PROJECT_NAME} PRE_BUILD
#     COMMAND ${CMAKE_COMMAND} -E echo "Copying from ${UI_FILES_SOURCE_DIR} to ${UI_FILES_DEST_DIR}"
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${UI_FILES_SOURCE_DIR} ${UI_FILES_DEST_DIR}
#     COMMAND ${CMAKE_COMMAND} -E echo "Copy completed"
#     VERBATIM
# )
add_custom_target(copy_ui_files
    COMMAND ${CMAKE_COMMAND} -E echo "Copying from ${UI_FILES_SOURCE_DIR} to ${UI_FILES_DEST_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${UI_FILES_SOURCE_DIR} ${UI_FILES_DEST_DIR}
    COMMAND ${CMAKE_COMMAND} -E echo "Copy completed"
    VERBATIM
)
add_dependencies(${PROJECT_NAME} copy_ui_files)
