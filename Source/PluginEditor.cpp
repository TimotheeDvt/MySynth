#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessorEditor::MySynthAudioProcessorEditor(MySynthAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p), oscComponent(audioProcessor.apvts, "OSC"), adsr(audioProcessor.apvts)
{
    setSize(400, 300);

    addAndMakeVisible(oscComponent);
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
	oscComponent.setBounds(10, 10, 90, 20);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}