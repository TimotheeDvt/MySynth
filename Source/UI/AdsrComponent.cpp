#include <juce_audio_processors/juce_audio_processors.h>
#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackSliderAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlidder);
    decaySliderAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlidder);
    sustainSliderAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlidder);
    releaseSliderAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlidder);

    setSliderParams(attackSlidder);
    setSliderParams(decaySlidder);
    setSliderParams(sustainSlidder);
    setSliderParams(releaseSlidder);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    attackSlidder.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlidder.setBounds(attackSlidder.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlidder.setBounds(decaySlidder.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlidder.setBounds(sustainSlidder.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}


void AdsrComponent::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(slider);
}