#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./UI/AdsrComponent.h"

class MySynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MySynthAudioProcessorEditor(MySynthAudioProcessor&);
    ~MySynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox ocsSelector;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> ocsSelectorAttachment;

	MySynthAudioProcessor& audioProcessor;
    AdsrComponent adsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySynthAudioProcessorEditor)
};
