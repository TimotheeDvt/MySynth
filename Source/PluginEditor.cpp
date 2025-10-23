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
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor()
{
}

void MySynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MySynthAudioProcessorEditor::resized()
{

}
