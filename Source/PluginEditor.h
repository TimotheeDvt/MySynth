#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MySynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MySynthAudioProcessorEditor(MySynthAudioProcessor&);
    ~MySynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox ocsSelector;
	juce::Slider attackSlidder;
	juce::Slider decaySlidder;
	juce::Slider sustainSlidder;
	juce::Slider releaseSlidder;

	using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	std::unique_ptr<ComboAttachment> ocsSelectorAttachment;
    std::unique_ptr<SliderAttachment> attackSliderAttachment;
	std::unique_ptr<SliderAttachment> decaySliderAttachment;
	std::unique_ptr<SliderAttachment> sustainSliderAttachment;
	std::unique_ptr<SliderAttachment> releaseSliderAttachment;

	MySynthAudioProcessor& audioProcessor;
	void setSliderParams(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySynthAudioProcessorEditor)
};
