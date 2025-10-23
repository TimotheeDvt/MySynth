#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec) {
	prepare(spec);
};

void OscData::getNextAudioBlock(juce::dsp::ProcessContextReplacing<float> context) {
	process(context);
};

void OscData::setWaveNote(const int midiNoteNumber) {
	setWaveFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
};

void OscData::setWaveFrequency(const float frequency) {
	setFrequency(frequency);
};

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