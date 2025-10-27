#include "AdsrGraphComponent.h"

AdsrGraph::AdsrGraph() {
        updatePath();
}

AdsrGraph::~AdsrGraph() {}

void AdsrGraph::paint(juce::Graphics& g) {
        auto bounds = getLocalBounds().toFloat().reduced(5.0f);

        g.setColour(juce::Colours::black);
        g.fillRoundedRectangle(bounds, 3.0f);

        g.setColour(juce::Colours::darkblue);
        g.drawRoundedRectangle(bounds, 3.0f, 1.0f);

        g.setColour(juce::Colours::cyan);
        g.strokePath(adsrPath, juce::PathStrokeType(2.5f));

        float totalTime = attackTime + decayTime + 0.3f + releaseTime;
        g.setColour(juce::Colours::white);
        g.setFont(12.0f);
        juce::String timeLabel = juce::String(totalTime, 2) + "s";
        g.drawText(timeLabel, bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 5, 15, juce::Justification::right);
}

void AdsrGraph::resized() {
        updatePath();
}

void AdsrGraph::updateAdsr(float attack, float decay, float sustain, float release) {
        attackTime = attack;
        decayTime = decay;
        sustainLevel = sustain;
        releaseTime = release;
        updatePath();
        repaint();
}

void AdsrGraph::updatePath() {
        auto bounds = getLocalBounds().toFloat().reduced(10.0f);

        adsrPath.clear();

        float totalTime = attackTime + decayTime + 0.3f + releaseTime;
        float width = bounds.getWidth();
        float height = bounds.getHeight();

        float x = bounds.getX();
        float y = bounds.getBottom();

        adsrPath.startNewSubPath(x, y);

        // Attack
        x += (attackTime / totalTime) * width;
        adsrPath.lineTo(x, bounds.getY());

        // Decay
        float sustainY = bounds.getY() + (1.0f - sustainLevel) * height;
        x += (decayTime / totalTime) * width;
        adsrPath.lineTo(x, sustainY);

        // Sustain
        x += (0.3f / totalTime) * width;
        adsrPath.lineTo(x, sustainY);

        // Release
        x += (releaseTime / totalTime) * width;
        adsrPath.lineTo(x, bounds.getBottom());
}