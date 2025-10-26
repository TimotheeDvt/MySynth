#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessor::MySynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    synth.addSound(new SynthSound());
    for (int i = 0; i < 8; ++i)
        synth.addVoice(new SynthVoice());
}

MySynthAudioProcessor::~MySynthAudioProcessor()
{
}

const juce::String MySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MySynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool MySynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool MySynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double MySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MySynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int MySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MySynthAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String MySynthAudioProcessor::getProgramName(int index)
{
    return {};
}

void MySynthAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void MySynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
	}
    filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void MySynthAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MySynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void MySynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
			auto& oscWave = *apvts.getRawParameterValue("OSC1");

			auto& fmFreq = *apvts.getRawParameterValue("FMFREQOSC1");
			auto& fmDepth = *apvts.getRawParameterValue("FMDEPTHOSC1");

			auto& attack = *apvts.getRawParameterValue("ATTACK");
			auto& decay = *apvts.getRawParameterValue("DECAY");
			auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
			auto& release = *apvts.getRawParameterValue("RELEASE");

			voice->getOscillator().setWaveType(oscWave.load());
            voice->getOscillator().setFMParams(fmDepth.load(), fmFreq.load());
			voice->update(attack.load(), decay.load(), sustain.load(), release.load());
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& filterFreq = *apvts.getRawParameterValue("FILTERFREQ");
    auto& filterRes = *apvts.getRawParameterValue("FILTERRES");
    filter.updateParams(filterType.load(), filterFreq.load(), filterRes.load());

    filter.process(buffer);
}


bool MySynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MySynthAudioProcessor::createEditor()
{
    return new MySynthAudioProcessorEditor(*this);
}

void MySynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{

}

void MySynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{

}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MySynthAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout MySynthAudioProcessor::createParams() {
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // Combo box switch oscillator type
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        "OSC1",
        "Oscillator 1",
        juce::StringArray{ "Sine", "Saw", "Square" },
        0
    ));

    // FREQUENCY MODULATOR
    // fm Frequ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FMFREQOSC1",
        "FM Frequency Osc1",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.3f},
        0.0f
	));
    // fm Depth
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FMDEPTHOSC1",
        "FM Depth Osc1",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.3f},
        0.0f
	));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "ATTACK",
        "Attack",
        juce::NormalisableRange<float>{0.1f, 1.0f, 0.01f},
        0.1f
	));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "DECAY",
        "Decay",
        juce::NormalisableRange<float>{0.1f, 1.0f, 0.01f},
        0.1f
    ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "SUSTAIN",
        "Sustain",
        juce::NormalisableRange<float>{0.1f, 1.0f, 0.01f},
        1.0f
    ));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "RELEASE",
        "Release",
        juce::NormalisableRange<float>{0.1f, 3.0f, 0.01f},
        0.4f
    ));

    // FILTER
    // Filter Type
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        "FILTERTYPE",
        "Filter Type",
        juce::StringArray{ "LowPass", "BandPass", "HighPass" },
        0
    ));
    // Filter Frequency
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FILTERFREQ",
        "Filter Frequency",
        juce::NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.3f},
        200.0f
    ));
    // Filter Resonance
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FILTERRES",
        "Filter Resonance",
        juce::NormalisableRange<float>{1.0f, 10.0f, 0.1f},
        1.0f
    ));

	return { params.begin(), params.end() };
}