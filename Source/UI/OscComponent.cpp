#include <juce_audio_processors/juce_audio_processors.h>
#include "OscComponent.h"

OscComponent::OscComponent(
        juce::AudioProcessorValueTreeState& apvts,
        juce::String waveSelectorId,
        juce::String oscGainId,
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

        setSliderLabel(oscGainSlider, oscGainLabel, oscGainAttachment, apvts, oscGainId, juce::Slider::SliderStyle::LinearHorizontal, false, false);
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

        juce::FlexBox oscFB;
        oscFB.flexDirection = juce::FlexBox::Direction::row;
        oscFB.justifyContent = juce::FlexBox::JustifyContent::center;
        oscFB.alignItems = juce::FlexBox::AlignItems::center;
        oscFB.items.add(
                juce::FlexItem(oscWaveSelector)
                        .withWidth(bounds.getWidth() / 2)
                        .withHeight(20)
        );
        oscFB.items.add(
                juce::FlexItem(oscGainSlider)
                        .withWidth(bounds.getWidth() / 2)
                        .withHeight(20)
        );
        // oscFB.items.add(
        //         juce::FlexItem(oscGainLabel)
        //                 .withWidth(sliderWidth)
        //                 .withHeight(15)
        // );

        fb.items.add(oscFB);

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
        juce::String paramId,
        juce::Slider::SliderStyle style, // = juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag
        bool showLabel, // = true
        bool showTextBox //= true
) {
        slider.setSliderStyle(style);
        if (showTextBox)
                slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
        else
                slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

        addAndMakeVisible(slider);

        attachment = std::make_unique<SliderAttachment>(apvts, paramId, slider);

        if (!showLabel)
                return;
        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
        label.setJustificationType(juce::Justification::centred);
        label.setFont(15.0f);

        addAndMakeVisible(label);
}