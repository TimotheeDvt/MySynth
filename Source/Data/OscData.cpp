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
	float freq = calculateFrequency(midiNoteNumber);
	setFrequency(freq + fmMod);
	lastMidiNote = midiNoteNumber;
};

void OscData::setWaveFrequency(const float frequency) {
        setFrequency(frequency + fmMod);
};

void OscData::setFMParams(const float depth, const float freq) {
        fmOsc.setFrequency(freq);
        fmDepth = depth;
        float frequency = calculateFrequency(lastMidiNote);
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

float OscData::calculateFrequency(int midiNoteNumber) {
	// If no scale is loaded, use standard 12-TET
	if (scale == nullptr || !scale->isLoaded()) {
		return juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber, referenceFrequency);
	}

	// Get scale info
	int scaleLength = (int)scale->getScaleLength();
	if (scaleLength <= 1) {
		return juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber, referenceFrequency);
	}

	// The last degree is the period/octave, actual scale has (scaleLength - 1) notes
	int degreesPerPeriod = scaleLength - 1;
	
	// Distance from reference note (A4 = MIDI 69)
	int noteDistance = midiNoteNumber - referenceNote;
	
	// Calculate how many periods (octaves) and which degree within the period
	int periods = noteDistance / degreesPerPeriod;
	int degreeIndex = noteDistance % degreesPerPeriod;
	
	// Handle negative modulo correctly
	if (degreeIndex < 0) {
		degreeIndex += degreesPerPeriod;
		periods -= 1;
	}

	// Get the ratio for this scale degree
	double ratio = scale->getRatio(degreeIndex);

	// Get the period ratio (e.g., 2.0 for octave, 3.0 for tritave)
	double periodRatio = scale->getRatio(scaleLength - 1);

	// Apply period transposition
	if (periods != 0) {
		ratio *= std::pow(periodRatio, periods);
	}

	// Calculate final frequency
	return referenceFrequency * (float)ratio;
}