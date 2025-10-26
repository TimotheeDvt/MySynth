#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessorEditor::MySynthAudioProcessorEditor(MySynthAudioProcessor& p)
: AudioProcessorEditor(&p),
  audioProcessor(p),
  oscComponent(audioProcessor.apvts, "OSC1", "FMFREQOSC1", "FMDEPTHOSC1"),
  filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES"),
  adsr(audioProcessor.apvts)
{
  setSize(600, 500);

  addAndMakeVisible(oscComponent);
  addAndMakeVisible(adsr);
  addAndMakeVisible(filter);
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
  const auto paddingX = 5;
  const auto paddingY = 35;

  oscComponent.setBounds(paddingX, paddingY, 300, 200);
  adsr.setBounds(oscComponent.getRight(), paddingY, 280, 400);
  filter.setBounds(paddingX, oscComponent.getBottom(), 300, 200);
}