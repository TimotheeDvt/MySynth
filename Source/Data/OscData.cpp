#include "OscData.h"
#include "ScaleData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec) {
        fmOsc.prepare(spec);
        prepare(spec);
        initialise([](float x) { return std::sin(x); });
};

void OscData::getNextAudioBlock(juce::dsp::ProcessContextReplacing<float> context) {
        juce::dsp::AudioBlock<const float> block = context.getOutputBlock();
        for (int ch = 0; ch < block.getNumChannels(); ++ch) {
                for (int s = 0; s < block.getNumSamples(); ++s) {
                        fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
                }
        }

        process(context);
};

void OscData::setWaveNote(const int midiNoteNumber) {
        float freq = scale != nullptr
                ? scale->calculateFrequency(midiNoteNumber)
                : juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        setFrequency(freq + fmMod);
        lastMidiNote = midiNoteNumber;
};

void OscData::setWaveFrequency(const float frequency) {
        setFrequency(frequency + fmMod);
};

void OscData::setFMParams(const float depth, const float freq) {
        fmOsc.setFrequency(freq);
        fmDepth = depth;
        float frequency = scale != nullptr
                ? scale->calculateFrequency(lastMidiNote)
                : juce::MidiMessage::getMidiNoteInHertz(lastMidiNote);
        setFrequency(frequency + fmMod);
}

void OscData::setWaveType(const int choice) {
        switch (choice) {
                case 0:
                        // Sine
                        initialise([](float x) { return std::sin(x); });
                        break;
                case 1:
                        // Saw
                        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
                        break;
                case 2:
                        // Square
                        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
                        break;
                default:
                        jassertfalse;
                        break;
        }
};

void OscData::setScale(ScaleData* scaleData) {
        scale = scaleData;
}