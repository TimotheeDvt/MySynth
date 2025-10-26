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

# Sources du projet
target_sources(MySynth
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h

        Source/SynthVoice.cpp
        Source/SynthVoice.h
        Source/SynthSound.h

        Source/UI/AdsrComponent.cpp
        Source/UI/AdsrComponent.h
        Source/UI/OscComponent.cpp
        Source/UI/OscComponent.h
        Source/UI/FilterComponent.cpp
        Source/UI/FilterComponent.h
        Source/UI/FFTComponent.cpp
        Source/UI/FFTComponent.h

        Source/Data/AdsrData.cpp
        Source/Data/AdsrData.h
        Source/Data/OscData.cpp
        Source/Data/OscData.h
        Source/Data/FilterData.cpp
        Source/Data/FilterData.h
)

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
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)