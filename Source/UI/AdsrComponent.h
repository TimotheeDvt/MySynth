#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class AdsrComponent  : public juce::Component {
public:
        AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
        ~AdsrComponent() override;

        void paint (juce::Graphics&) override;
        void resized() override;

private:
        void setSliderParams(juce::Slider& slider);

        using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
        std::unique_ptr<SliderAttachment> attackSliderAttachment;
        std::unique_ptr<SliderAttachment> decaySliderAttachment;
        std::unique_ptr<SliderAttachment> sustainSliderAttachment;
        std::unique_ptr<SliderAttachment> releaseSliderAttachment;

        juce::Slider attackSlidder;
        juce::Slider decaySlidder;
        juce::Slider sustainSlidder;
        juce::Slider releaseSlidder;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};