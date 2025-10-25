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
    g.setColour(juce::Colours::darkblue);
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto sliderWidth = (float)bounds.getWidth() / 4;
    const auto sliderHeight = (float)bounds.getHeight();

    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    fb.alignItems = juce::FlexBox::AlignItems::center;

    fb.items.add(
        juce::FlexItem(attackSlidder)
            .withWidth(sliderWidth)
            .withHeight(sliderHeight)
    );
    fb.items.add(
        juce::FlexItem(decaySlidder)
            .withWidth(sliderWidth)
            .withHeight(sliderHeight)
    );
    fb.items.add(
        juce::FlexItem(sustainSlidder)
            .withWidth(sliderWidth)
            .withHeight(sliderHeight)
    );
    fb.items.add(
        juce::FlexItem(releaseSlidder)
            .withWidth(sliderWidth)
            .withHeight(sliderHeight)
    );

    fb.performLayout(bounds);
}


void AdsrComponent::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(slider);
}