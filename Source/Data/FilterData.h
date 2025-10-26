#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class FilterData {
        public:
        void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
        void process(juce::AudioBuffer<float>& buffer);
        void updateParams(const int filterType, const float frequency, const float resonance);
        void reset();

        private:
        juce::dsp::StateVariableTPTFilter<float> filter;
        bool isPrepared { false };
};