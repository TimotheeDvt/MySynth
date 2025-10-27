#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "PluginProcessor.h"
#include "./UI/AdsrComponent.h"
#include "./UI/OscComponent.h"
#include "./UI/FilterComponent.h"
#include "./UI/ScaleComponent.h"
#include "./UI/FFTComponent.h"

class MySynthAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
        MySynthAudioProcessorEditor(MySynthAudioProcessor&);
        ~MySynthAudioProcessorEditor() override;

        void paint(juce::Graphics&) override;
        void resized() override;

private:
        MySynthAudioProcessor& audioProcessor;
        OscComponent osc;
        AdsrComponent adsr;
        FilterComponent filter;
        FFTComponent fft;
        ScaleComponent scale;
        juce::MidiKeyboardComponent keyboard;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySynthAudioProcessorEditor)
};