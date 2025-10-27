#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "AdsrGraphComponent.h"

class AdsrComponent : public juce::Component, private juce::Slider::Listener {
public:
        AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
        ~AdsrComponent() override;

        void paint (juce::Graphics&) override;
        void resized() override;

private:
        void setSliderParams(juce::Slider& slider);
        void sliderValueChanged(juce::Slider* slider) override;

        AdsrGraph adsrGraph;

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