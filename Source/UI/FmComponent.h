#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class FmComponent  : public juce::Component
{
public:
    FmComponent(juce::AudioProcessorValueTreeState& apvts);
    ~FmComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> fmFreqSliderAttachment;
    std::unique_ptr<SliderAttachment> fmDepthSliderAttachment;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmComponent)
};
