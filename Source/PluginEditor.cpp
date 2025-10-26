#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessorEditor::MySynthAudioProcessorEditor(MySynthAudioProcessor& p)
: AudioProcessorEditor(&p),
  audioProcessor(p),
  oscComponent(audioProcessor.apvts, "OSC1", "FMFREQOSC1", "FMDEPTHOSC1"),
  filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES"),
  adsr(audioProcessor.apvts),
  keyboard(audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
  setSize(600, 580);

  addAndMakeVisible(oscComponent);
  addAndMakeVisible(adsr);
  addAndMakeVisible(filter);
  addAndMakeVisible(keyboard);
  addAndMakeVisible(fft);

  audioProcessor.setFFTComponent(&fft);
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor() {
  audioProcessor.setFFTComponent(nullptr);
}

void MySynthAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::black);
}

void MySynthAudioProcessorEditor::resized() {
  const auto paddingX = 5;
  const auto paddingY = 35;
  const auto keyboardHeight = 70;

  oscComponent.setBounds(paddingX, paddingY, 300, 200);
  adsr.setBounds(oscComponent.getRight(), paddingY, 280, 200);
  filter.setBounds(paddingX, oscComponent.getBottom(), 300, 200);

  fft.setBounds(
    filter.getRight(),
    adsr.getBottom(),
    280,
    200
  );

  keyboard.setBounds(
    paddingX,
    filter.getBottom() + 10,
    getWidth() - (paddingX * 2),
    keyboardHeight
  );
}