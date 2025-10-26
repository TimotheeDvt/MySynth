#include <juce_audio_processors/juce_audio_processors.h>
#include "FilterComponent.h"

FilterComponent::FilterComponent(
        juce::AudioProcessorValueTreeState& apvts,
        juce::String filterTypeSelectorId,
        juce::String filterFreqId,
        juce::String filterResId
) {
        juce::StringArray filterTypeChoices { "LowPass", "BandPass", "HighPass" };
        filterTypeSelector.addItemList(filterTypeChoices, 1);
        addAndMakeVisible(filterTypeSelector);

        filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
                apvts,
                filterTypeSelectorId,
                filterTypeSelector
        );

        setSliderLabel(filterFreqSlider, filterFreqLabel, filterFreqAttachment, apvts, filterFreqId);
        setSliderLabel(filterResSlider, filterResLabel, filterResAttachment, apvts, filterResId);
}

FilterComponent::~FilterComponent() {
}

void FilterComponent::paint (juce::Graphics& g) {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::darkblue);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);

        // g.setColour (juce::Colours::white);
        // g.setFont (juce::FontOptions (14.0f));
        // g.drawText ("FilterComponent", getLocalBounds(),
        //             juce::Justification::centred, true);   // draw some placeholder text
}

void FilterComponent::resized() {
        const auto bounds = getLocalBounds().reduced(10);
        const auto sliderWidth = (float)bounds.getWidth() - 10;
        const auto sliderHeight = (float)bounds.getHeight() / 2 - 50;
        juce::FlexBox fb;
        fb.flexDirection = juce::FlexBox::Direction::column;
        fb.justifyContent = juce::FlexBox::JustifyContent::center;

        fb.items.add(
                juce::FlexItem(filterTypeSelector)
                        .withWidth(sliderWidth)
                        .withHeight(20)
        );

        fb.items.add(
                juce::FlexItem(filterFreqSlider)
                        .withWidth(sliderWidth)
                        .withHeight(75)
        );

        fb.items.add(
                juce::FlexItem(filterFreqLabel)
                        .withWidth(sliderWidth)
                        .withHeight(15)
        );

        fb.items.add(
                juce::FlexItem(filterResSlider)
                        .withWidth(sliderWidth)
                        .withHeight(75)
        );

        fb.items.add(
                juce::FlexItem(filterResLabel)
                        .withWidth(sliderWidth)
                        .withHeight(15)
        );

        fb.performLayout(bounds);

        // const auto bounds = getLocalBounds();
        // filterTypeSelector.setBounds(0, 0, 90, 20);
        // filterFreqSlider.setBounds(0, 80, bounds.getWidth() / 2 - 10, 90);
        // filterFreqLabel.setBounds(filterFreqSlider.getX(), filterFreqSlider.getY() - 20, filterFreqSlider.getWidth(), 20);
        // filterResSlider.setBounds(filterFreqSlider.getRight(), 80, bounds.getWidth() / 2 - 10, 90);
        // filterResLabel.setBounds(filterResSlider.getX(), filterFreqSlider.getY() - 20, filterFreqSlider.getWidth(), 20);
}

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void FilterComponent::setSliderLabel (
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