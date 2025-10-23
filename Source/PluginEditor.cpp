#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessorEditor::MySynthAudioProcessorEditor(MySynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), adsr (audioProcessor.apvts)
{
    setSize(400, 300);

    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    ocsSelectorAttachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "OSC", ocsSelector);

    addAndMakeVisible(adsr);
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
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}