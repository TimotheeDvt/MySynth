cmake_minimum_required(VERSION 3.15)

project(MySynth VERSION 1.0.0)

# Forcer l'utilisation de chemins courts
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Chemin vers JUCE
set(JUCE_DIR "C:/dev/JUCE" CACHE PATH "Path to JUCE")
add_subdirectory(${JUCE_DIR} JUCE)

# Créer le plugin
juce_add_plugin(MySynth
        COMPANY_NAME "VotreSociete"
        PLUGIN_MANUFACTURER_CODE Manu
        PLUGIN_CODE Syn1
        FORMATS Standalone
        PRODUCT_NAME "MySynth"
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        COPY_PLUGIN_AFTER_BUILD FALSE
        PLUGIN_NAME "MySynth"
)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp"
)

# Sources du projet
target_sources(MySynth PRIVATE ${SRC_FILES})

# Standalone target
set(STANDALONE_TARGET "${PROJECT_NAME}_Standalone")

if(TARGET ${STANDALONE_TARGET})
    target_sources(${STANDALONE_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Resources/MySynth.rc")
    set_target_properties(${STANDALONE_TARGET} PROPERTIES
        OUTPUT_NAME "MySynth"
    )
endif()

# Modules JUCE nécessaires
target_compile_definitions(MySynth
PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
)

target_link_libraries(MySynth
PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_gui_basics
PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)