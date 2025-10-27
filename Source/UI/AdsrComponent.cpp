#include <juce_audio_processors/juce_audio_processors.h>
#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts) {
        using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

        attackSliderAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlidder);
        decaySliderAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlidder);
        sustainSliderAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlidder);
        releaseSliderAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlidder);

        setSliderParams(attackSlidder);
        setSliderParams(decaySlidder);
        setSliderParams(sustainSlidder);
        setSliderParams(releaseSlidder);

        attackSlidder.addListener(this);
        decaySlidder.addListener(this);
        sustainSlidder.addListener(this);
        releaseSlidder.addListener(this);

        addAndMakeVisible(adsrGraph);

        adsrGraph.updateAdsr(
                attackSlidder.getValue(),
                decaySlidder.getValue(),
                sustainSlidder.getValue(),
                releaseSlidder.getValue()
        );
}

AdsrComponent::~AdsrComponent() {
}

void AdsrComponent::paint (juce::Graphics& g) {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::darkblue);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
}

void AdsrComponent::resized() {
        const auto bounds = getLocalBounds().reduced(10);
        const auto sliderWidth = (float)bounds.getWidth() / 4;
        const auto sliderHeight = (float)bounds.getHeight() / 2;

        juce::FlexBox globalFB;

        juce::FlexBox slidersFB;
        slidersFB.flexDirection = juce::FlexBox::Direction::row;
        slidersFB.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
        slidersFB.alignItems = juce::FlexBox::AlignItems::center;

        slidersFB.items.add(
                juce::FlexItem(attackSlidder)
                        .withWidth(sliderWidth)
                        .withHeight(sliderHeight)
        );
        slidersFB.items.add(
                juce::FlexItem(decaySlidder)
                        .withWidth(sliderWidth)
                        .withHeight(sliderHeight)
        );
        slidersFB.items.add(
                juce::FlexItem(sustainSlidder)
                        .withWidth(sliderWidth)
                        .withHeight(sliderHeight)
        );
        slidersFB.items.add(
                juce::FlexItem(releaseSlidder)
                        .withWidth(sliderWidth)
                        .withHeight(sliderHeight)
        );

        globalFB.flexDirection = juce::FlexBox::Direction::column;
        globalFB.justifyContent = juce::FlexBox::JustifyContent::center;
        globalFB.alignItems = juce::FlexBox::AlignItems::center;

        globalFB.items.add(
                juce::FlexItem(slidersFB)
                        .withWidth(bounds.getWidth())
                        .withHeight(bounds.getHeight() / 2)
        );

        globalFB.items.add(
                juce::FlexItem(adsrGraph)
                        .withWidth(bounds.getWidth())
                        .withHeight(bounds.getHeight() / 2)
        );

        globalFB.performLayout(bounds);
}


void AdsrComponent::setSliderParams(juce::Slider& slider) {
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
        addAndMakeVisible(slider);
}

void AdsrComponent::sliderValueChanged(juce::Slider* slider) {
        adsrGraph.updateAdsr(
                attackSlidder.getValue(),
                decaySlidder.getValue(),
                sustainSlidder.getValue(),
                releaseSlidder.getValue()
        );
}