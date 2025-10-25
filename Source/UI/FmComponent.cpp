#include <juce_audio_processors/juce_audio_processors.h>
#include "FmComponent.h"

//==============================================================================
FmComponent::FmComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    fmFreqSliderAttachment = std::make_unique<SliderAttachment>(apvts, "FMFREQ", fmFreqSlider);
    fmDepthSliderAttachment = std::make_unique<SliderAttachment>(apvts, "FMDEPTH", fmDepthSlider);

    setSliderParams(fmFreqSlider);
    setSliderParams(fmDepthSlider);
}

FmComponent::~FmComponent()
{
}

void FmComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::darkblue);
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
}

void FmComponent::resized()
{
    juce::FlexBox fb;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    fb.alignItems = juce::FlexBox::AlignItems::center;

    fb.items.add(
        juce::FlexItem(fmFreqSlider)
            .withWidth(90)
            .withHeight(90)
    );
    fb.items.add(
        juce::FlexItem(fmDepthSlider)
            .withWidth(90)
            .withHeight(90)
    );

    fb.performLayout(getLocalBounds().reduced(10));
}

void FmComponent::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    slider.setNumDecimalPlacesToDisplay(1);
    slider.textFromValueFunction= [](double value) {
        if (value >= 10.0)
            return juce::String((int)value);
        else
            return juce::String(value, 1);
    };
    addAndMakeVisible(slider);
}