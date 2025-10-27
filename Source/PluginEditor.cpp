#include "PluginProcessor.h"
#include "PluginEditor.h"

MySynthAudioProcessorEditor::MySynthAudioProcessorEditor(MySynthAudioProcessor& p)
        : AudioProcessorEditor(&p),
        audioProcessor(p),
        oscComponent(audioProcessor.apvts, "OSC1", "FMFREQOSC1", "FMDEPTHOSC1"),
        filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES"),
        adsr(audioProcessor.apvts),
        keyboard(audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
        setSize(600, 580);

        addAndMakeVisible(oscComponent);
        addAndMakeVisible(adsr);
        addAndMakeVisible(filter);
        addAndMakeVisible(fft);
        addAndMakeVisible(scale);
        addAndMakeVisible(keyboard);

        audioProcessor.setFFTComponent(&fft);
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor() {
        audioProcessor.setFFTComponent(nullptr);
}

void MySynthAudioProcessorEditor::paint(juce::Graphics& g) {
        g.fillAll(juce::Colours::black);

        // Write "Oscillator", "Filter", "ADSR" labels
        g.setColour(juce::Colours::white);
        g.setFont(juce::FontOptions(16.0f));
        g.drawText("Oscillator", oscComponent.getX(), 10, oscComponent.getWidth(), 20, juce::Justification::centred);
        g.drawText("Filter", filter.getX(), 10, filter.getWidth(), 20, juce::Justification::centred);
        g.drawText("ADSR", adsr.getX(), 10, adsr.getWidth(), 20, juce::Justification::centred);

        g.drawText("Scale", scale.getX(), scale.getY() - 25, scale.getWidth(), 20, juce::Justification::centred);
        g.drawText("Frequency Spectrum", fft.getX(), fft.getY() - 25, fft.getWidth(), 20, juce::Justification::centred);
}

void MySynthAudioProcessorEditor::resized() {
        const auto paddingX = 5;
        const auto paddingY = 35;

        /****
         * ____________________________
         * |   OSC  |  ADSR  | Filter |
         * |    Scale    |     FFT    |
         * |         Keyboard         |
         * ----------------------------
         ****/

        oscComponent.setBounds(
                paddingX,
                paddingY,
                getWidth() / 4 - paddingX,
                200
        );
        adsr.setBounds(
                oscComponent.getRight() + paddingX,
                paddingY,
                getWidth() / 2 - 2*paddingX,
                200
        );
        filter.setBounds(
                adsr.getRight() + paddingX,
                paddingY,
                getWidth() / 4 - paddingX,
                200
        );

        scale.setBounds(
                oscComponent.getX(),
                oscComponent.getBottom() + paddingY,
                getWidth() / 2 - paddingX,
                200
        );
        fft.setBounds(
                scale.getRight() + paddingX,
                scale.getY(),
                getWidth() / 2 - 2*paddingX,
                200
        );

        const auto keyboardheight = 70;
        keyboard.setBounds(
                paddingX,
                getHeight() - paddingX - keyboardheight,
                getWidth() - 2*paddingX,
                keyboardheight
        );
}