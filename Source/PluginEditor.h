#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./UI/AdsrComponent.h"
#include "./UI/OscComponent.h"

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySynthAudioProcessorEditor)
};
