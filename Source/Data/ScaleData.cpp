#include "ScaleData.h"

float ScaleData::calculateFrequency(int midiNoteNumber) {
        // If no scale is loaded, use standard 12-TET
        if (!isLoaded()) {
                return juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber, referenceFrequency);
        }

        // Get scale info
        int scaleLength = (int)getScaleLength();
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
        double ratio = getRatio(degreeIndex);

        // Get the period ratio (e.g., 2.0 for octave, 3.0 for tritave)
        double periodRatio = getRatio(scaleLength - 1);

        // Apply period transposition
        if (periods != 0) {
                ratio *= std::pow(periodRatio, periods);
        }

        // Calculate final frequency
        return referenceFrequency * (float)ratio;
}