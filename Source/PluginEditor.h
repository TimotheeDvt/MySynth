#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"
#include "./UI/AdsrComponent.h"
#include "./UI/OscComponent.h"
#include "./UI/FmComponent.h"

class MySynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MySynthAudioProcessorEditor(MySynthAudioProcessor&);
    ~MySynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
	MySynthAudioProcessor& audioProcessor;
    OscComponent oscComponent;
    AdsrComponent adsr;
    FmComponent fm;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySynthAudioProcessorEditor)
};