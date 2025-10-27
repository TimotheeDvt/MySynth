#include <juce_audio_processors/juce_audio_processors.h>
#include "ScaleComponent.h"

ScaleComponent::ScaleComponent() {
        loadButton.setButtonText("Load Scale");
        loadButton.onClick = [this] { openFileChooser(); };
        addAndMakeVisible(loadButton);
}

ScaleComponent::~ScaleComponent() {
}

void ScaleComponent::openFileChooser() {
        juce::File initialDir("C:\\dev\\scales");

        fileChooser = std::make_unique<juce::FileChooser>(
                "Please select the scale you want to load...",
                initialDir,
                "*.scl"
        );

        auto folderChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(folderChooserFlags, [this] (const juce::FileChooser& chooser) {
                juce::File scaleFile (chooser.getResult());

                if (scaleFile.existsAsFile()) {
                        scale.loadFromFile(scaleFile.getFullPathName().toStdString(), scaleFile.getFileNameWithoutExtension().toStdString());
                        repaint();
                }
        });
}

void ScaleComponent::paint(juce::Graphics& g) {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::darkblue);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);

        auto bounds = getLocalBounds().reduced(10);

        g.setColour(juce::Colours::white);
        g.setFont(14.0f);

        if (scale.isLoaded()) {
                g.setFont(20.0f);
                g.drawText(scale.getName(), 0, 6, bounds.getWidth(), 30, juce::Justification::centred);

                g.setFont(15.0f);
                juce::String info = juce::String(scale.getScaleLength()) + " notes";
                g.drawText(info, 0, 40, bounds.getWidth(), 25, juce::Justification::centred);

                g.setFont(17.0f);
                juce::String description = juce::String(scale.getDescription());
                g.drawMultiLineText(scale.getDescription(), 15, bounds.getY() + bounds.getHeight() / 2, bounds.getWidth() - 15, juce::Justification::centred);
        } else {
                g.drawText("No scale loaded", bounds, juce::Justification::centred);
        }
}

void ScaleComponent::resized() {
        auto bounds = getLocalBounds().reduced(10);

        loadButton.setBounds(bounds.removeFromBottom(30).reduced(20, 0));
        repaint();
}