#pragma once
#include <juce_dsp/juce_dsp.h>

class ScaleData;

class OscData : public juce::dsp::Oscillator<float> {
public:
	void prepareToPlay(juce::dsp::ProcessSpec spec);
	void getNextAudioBlock(juce::dsp::ProcessContextReplacing<float> context);
	void setWaveNote(const int midiNoteNumber);
	void setWaveFrequency(const float frequency);
	void setWaveType(const int choice);
	void setFMParams(const float depth, const float freq);

	void setScale(ScaleData* scaleData);

private:
	float calculateFrequency(int midiNoteNumber);
	juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin(x);} };
	float fmMod { 0.0f };
	float fmDepth { 0.0f };
	int lastMidiNote { 0 };

	ScaleData* scale { nullptr };
	float referenceFrequency { 440.0f };
	int referenceNote { 69 }; // MIDI note 69 = A4
};