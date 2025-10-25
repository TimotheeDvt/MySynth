#include <juce_audio_processors/juce_audio_processors.h>
#include "OscComponent.h"

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    juce::StringArray waveChoices { "Sine", "Saw", "Square" };
	oscWaveSelector.addItemList(waveChoices, 1);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        apvts,
        waveSelectorId,
        oscWaveSelector
	);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::darkblue);
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
}

void OscComponent::resized()
{
	oscWaveSelector.setBounds(0, 0, 90, 20);
}