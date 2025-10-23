#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessorEditor::MySynthAudioProcessorEditor(MySynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);

    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    ocsSelectorAttachment   = std::make_unique<ComboAttachment> (audioProcessor.apvts, "OSC",       ocsSelector);
    attackSliderAttachment  = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK",    attackSlidder);
    decaySliderAttachment   = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY",     decaySlidder);
    sustainSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN",   sustainSlidder);
    releaseSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE",   releaseSlidder);

	setSliderParams(attackSlidder);
	setSliderParams(decaySlidder);
	setSliderParams(sustainSlidder);
	setSliderParams(releaseSlidder);
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor()
{
}

void MySynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    

}

void MySynthAudioProcessorEditor::resized()
{
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getHeight() / 2 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);
	attackSlidder.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlidder.setBounds(attackSlidder.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlidder.setBounds(decaySlidder.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlidder.setBounds(sustainSlidder.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void MySynthAudioProcessorEditor::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(slider);
}