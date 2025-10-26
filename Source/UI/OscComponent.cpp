#include <juce_audio_processors/juce_audio_processors.h>
#include "OscComponent.h"

OscComponent::OscComponent(
        juce::AudioProcessorValueTreeState& apvts,
        juce::String waveSelectorId,
        juce::String fmFreqId,
        juce::String fmDepthId
) {
        juce::StringArray waveChoices { "Sine", "Saw", "Square" };
        oscWaveSelector.addItemList(waveChoices, 1);
        addAndMakeVisible(oscWaveSelector);

        oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
                apvts,
                waveSelectorId,
                oscWaveSelector
        );

        setSliderLabel(fmFreqSlider, fmFreqLabel, fmFreqAttachment, apvts, fmFreqId);
        setSliderLabel(fmDepthSlider, fmDepthLabel, fmDepthAttachment, apvts, fmDepthId);
}

OscComponent::~OscComponent() {
}

void OscComponent::paint (juce::Graphics& g) {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::darkblue);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
}

void OscComponent::resized() {
        const auto bounds = getLocalBounds().reduced(10);
        const auto sliderWidth = (float)bounds.getWidth() - 10;
        const auto sliderHeight = (float)bounds.getHeight() / 2 - 50;
        juce::FlexBox fb;
        fb.flexDirection = juce::FlexBox::Direction::column;
        fb.justifyContent = juce::FlexBox::JustifyContent::center;

        fb.items.add(
                juce::FlexItem(oscWaveSelector)
                        .withWidth(sliderWidth)
                        .withHeight(20)
        );

        fb.items.add(
                juce::FlexItem(fmFreqSlider)
                        .withWidth(sliderWidth)
                        .withHeight(75)
        );

        fb.items.add(
                juce::FlexItem(fmFreqLabel)
                        .withWidth(sliderWidth)
                        .withHeight(15)
        );

        fb.items.add(
                juce::FlexItem(fmDepthSlider)
                        .withWidth(sliderWidth)
                        .withHeight(75)
        );

        fb.items.add(
                juce::FlexItem(fmDepthLabel)
                        .withWidth(sliderWidth)
                        .withHeight(15)
        );

        fb.performLayout(bounds);
}

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void OscComponent::setSliderLabel (
        juce::Slider& slider,
        juce::Label& label,
        std::unique_ptr<SliderAttachment>& attachment,
        juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId
) {
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);

        addAndMakeVisible(slider);

        attachment = std::make_unique<SliderAttachment>(apvts, paramId, slider);

        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
        label.setJustificationType(juce::Justification::centred);
        label.setFont(15.0f);

        addAndMakeVisible(label);
}