#include <juce_audio_processors/juce_audio_processors.h>
#include "ScaleComponent.h"
#include "../PluginProcessor.h"

ScaleComponent::ScaleComponent(MySynthAudioProcessor& proc)
	: processor(proc)
{
        loadButton.setButtonText("Load Scale");
        loadButton.onClick = [this] { openFileChooser(); };
        addAndMakeVisible(loadButton);

        clearButton.setButtonText("Clear");
        clearButton.onClick = [this] {
                processor.getScaleData().clear();
                repaint();
        };
        addAndMakeVisible(clearButton);
}

ScaleComponent::~ScaleComponent() {
}

void ScaleComponent::openFileChooser() {
        juce::File initialDir("C:/dev/MySynth/scales");

        fileChooser = std::make_unique<juce::FileChooser>(
                "Please select the scale you want to load...",
                initialDir,
                "*.scl"
        );

        auto folderChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(folderChooserFlags, [this] (const juce::FileChooser& chooser) {
                juce::File scaleFile (chooser.getResult());

                if (scaleFile.existsAsFile()) {
                        processor.getScaleData().loadFromFile(
				scaleFile.getFullPathName().toStdString(),
				scaleFile.getFileNameWithoutExtension().toStdString()
			);
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
        g.setFont(17.0f);

	auto& scaleData  = processor.getScaleData();

        if (scaleData.isLoaded()) {
                g.setFont(20.0f);
                g.drawText(scaleData.getName(), 0, 6, bounds.getWidth(), 30, juce::Justification::centred);

                g.setFont(15.0f);
                juce::String info = juce::String(scaleData.getScaleLength()) + " notes";
                g.drawText(info, 0, 40, bounds.getWidth(), 25, juce::Justification::centred);

                g.setFont(17.0f);
                juce::String description = juce::String(scaleData.getDescription());
                g.drawMultiLineText(scaleData.getDescription(), 15, bounds.getY() + bounds.getHeight() / 2, bounds.getWidth() - 15, juce::Justification::centred);
        } else {
                g.drawMultiLineText("No scale loaded\nDefault to 12-TET", 15, bounds.getY() + bounds.getHeight() / 2, bounds.getWidth() - 15, juce::Justification::centred);
        }
}

void ScaleComponent::resized() {
        auto bounds = getLocalBounds().reduced(10);

        loadButton.setBounds(
                10,
                bounds.getBottom() - 40,
                (bounds.getWidth() - 10) / 3 * 2,
                30
        );
        clearButton.setBounds(
                loadButton.getRight() + 10,
                bounds.getBottom() - 40,
                (bounds.getWidth() - 10) / 3,
                30
        );
        repaint();
}