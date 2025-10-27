#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Data/ScaleData.h"

class MySynthAudioProcessor;

class ScaleComponent : public juce::Component {
public:
        ScaleComponent(MySynthAudioProcessor& proc);
        ~ScaleComponent() override;

        void paint(juce::Graphics&) override;
        void resized() override;

private:
        void openFileChooser();

        std::unique_ptr<juce::FileChooser> fileChooser;
        MySynthAudioProcessor& processor;

        juce::TextButton loadButton;
        juce::TextButton clearButton;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScaleComponent)
};