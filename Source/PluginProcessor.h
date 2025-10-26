#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "SynthVoice.h"
#include "SynthSound.h"
#include "Data/FilterData.h"

class FFTComponent;

class MySynthAudioProcessor : public juce::AudioProcessor {
public:
    MySynthAudioProcessor();
    ~MySynthAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    #endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
	juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParams() };

    juce::MidiKeyboardState keyboardState;

    void setFFTComponent(FFTComponent* fftComp) { fftComponent = fftComp; }

private:
    juce::Synthesiser synth;
    FilterData filter;
    FFTComponent* fftComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySynthAudioProcessor)
};