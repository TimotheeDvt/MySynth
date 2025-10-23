#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {
public:
	void prepareToPlay(juce::dsp::ProcessSpec spec);
	void getNextAudioBlock(juce::dsp::ProcessContextReplacing<float> context);
	void setWaveNote(const int midiNoteNumber);
	void setWaveFrequency(const float frequency);
	void setWaveType(const int choice);

private:
	
};