#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <fstream>
#include "../../Libs/scala_scl.h"

class ScaleData {
public:
        ScaleData() = default;
        ~ScaleData() = default;

        scala::scale scale;

        void loadFromFile(const std::string& filename, const std::string& scaleName) {
                std::ifstream input_file(filename);
                if (input_file.is_open()) {
                        scale = scala::read_scl(input_file);
                        scale.name = scaleName;
                        input_file.close();
                }
        }

        size_t getScaleLength() { return scale.getScaleLength(); }
        double getRatio(int i) { return scale.getRatio(i); }
        bool isLoaded() { return !scale.degrees.empty() && scale.degrees.size() > 1; }
        juce::String getName() { return juce::String(scale.name); }
        juce::String getDescription() { return juce::String(scale.getDescription()); }
        void clear() {
                scale.degrees.clear();
                scale.name.clear();
                scale.description.clear();
        }
};
