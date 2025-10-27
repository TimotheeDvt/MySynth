#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class AdsrGraph : public juce::Component {
public:
        AdsrGraph();
        ~AdsrGraph() override;

        void paint(juce::Graphics& g) override;
        void resized() override;

        void updateAdsr(float attack, float decay, float sustain, float release);

private:
        float attackTime = 0.1f;
        float decayTime = 0.1f;
        float sustainLevel = 1.0f;
        float releaseTime = 0.1f;

        juce::Path adsrPath;
        void updatePath();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AdsrGraph)
};