#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Data/ScaleData.h"

class ScaleComponent : public juce::Component {
public:
        ScaleComponent();
        ~ScaleComponent() override;

        void paint(juce::Graphics&) override;
        void resized() override;

private:
        void openFileChooser();

        std::unique_ptr<juce::FileChooser> fileChooser;
        ScaleData scale;

        juce::TextButton loadButton;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScaleComponent)
};