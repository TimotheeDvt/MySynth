#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::ComboBox oscWaveSelector;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

	juce::Slider fmFreqSlider;
	juce::Slider fmDepthSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> fmFreqAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;

    juce::Label fmFreqLabel {"FMFREQLABEL", "FM Freq"};
    juce::Label fmDepthLabel {"FMDEPTHLABEL", "FM Depth"};

    void setSliderLabel (juce::Slider& slider, juce::Label& label,
        std::unique_ptr<SliderAttachment>& attachment,
        juce::AudioProcessorValueTreeState& apvts, juce::String id
    );

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};