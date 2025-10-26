#include "FFTComponent.h"
#define _USE_MATH_DEFINES
#include <complex>
#include <cmath>
#include <math.h>

FFTComponent::FFTComponent()
        : forwardFFT(fftOrder),
        window(fftSize, juce::dsp::WindowingFunction<float>::hann)
{
        setOpaque(true);
        startTimerHz(30); // Rafraîchir 30 fois par seconde

        for (auto& s : scopeData)
                s = 0.0f;
        for (auto& s : smoothedScopeData)
                s = 0.0f;
}

FFTComponent::~FFTComponent() {
}

void FFTComponent::paint(juce::Graphics& g) {
        g.fillAll(juce::Colours::black);

        g.setColour(juce::Colours::darkblue);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);

        auto width = (float) getLocalBounds().getWidth();
        auto height = (float) getLocalBounds().getHeight();

        const float fMin = 20.0f;
        const float sampleRateLocal = (currentSampleRate > 0.0) ? (float) currentSampleRate : 48000.0f;
        const float fMax = sampleRateLocal * 0.5f;
        const int numBins = fftSize / 2;

        g.setColour(juce::Colours::darkgrey.withAlpha(0.3f));
        for (int db = -60; db <= 0; db += 20) {
                float y = juce::jmap((float)db, -60.0f, 0.0f, height - 20.0f, 10.0f);
                g.drawHorizontalLine((int)y, 0.0f, width);
                g.drawText(juce::String(db) + " dB", 5, (int)y - 10, 40, 20, juce::Justification::left);
        }

        const std::vector<float> gridFreqs = { 20.0f, 50.0f, 100.0f, 200.0f, 500.0f, 1000.0f, 2000.0f, 5000.0f, 10000.0f, 20000.0f };
        g.setColour(juce::Colours::darkgrey.withAlpha(0.25f));
        const float logMin = std::log10(std::max(fMin, 1.0f));
        const float logMax = std::log10(std::max(fMax, fMin + 1.0f));
        for (auto f : gridFreqs) {
                if (f > fMax)
                        break;
                float pos = (std::log10(std::max(f, fMin)) - logMin) / (logMax - logMin);
                float x = juce::jlimit(0.0f, 1.0f, pos) * width;
                g.drawVerticalLine((int)x, 0.0f, height);
                juce::String label;
                if (f >= 1000.0f)
                        label = juce::String((int)(f / 1000.0f)) + "k";
                else
                        label = juce::String((int)f);
                g.drawText(label, (int)x - 18, (int)height - 18, 36, 15, juce::Justification::centred);
        }

        g.setColour(juce::Colours::cyan.withAlpha(0.8f));
        juce::Path spectralPath;
        spectralPath.preallocateSpace((size_t)std::max(32, (int)width));

        bool firstPoint = true;
        for (int i = 1; i < numBins; ++i) {
                float freq = (float)i * (fMax / (float)numBins);
                freq = std::max(freq, fMin);

                float pos = (std::log10(freq) - logMin) / (logMax - logMin);
                pos = juce::jlimit(0.0f, 1.0f, pos);
                float x = pos * width;

                float levelNorm = smoothedScopeData[i];
                float y = juce::jmap(levelNorm, 0.0f, 1.0f, height - 20.0f, 10.0f);

                if (firstPoint) {
                        spectralPath.startNewSubPath(x, y);
                        firstPoint = false;
                } else {
                        spectralPath.lineTo(x, y);
                }
        }

        g.strokePath(spectralPath, juce::PathStrokeType(1.5f));

        if (!spectralPath.isEmpty()) {
                juce::Path fillPath = spectralPath;
                fillPath.lineTo(width, height);
                fillPath.lineTo(0.0f, height);
                fillPath.closeSubPath();
                g.setColour(juce::Colours::cyan.withAlpha(0.15f));
                g.fillPath(fillPath);
        }

        drawFilterCurve(g);
}

void FFTComponent::drawFilterCurve(juce::Graphics& g) {
        auto width = (float) getLocalBounds().getWidth();
        auto height = (float) getLocalBounds().getHeight();

        g.setColour(juce::Colours::yellow.withAlpha(0.9f));
        juce::Path filterPath;

        const int numPoints = 300;
        const float minFreq = 20.0f;
        const float maxFreq = (float)(currentSampleRate / 2.0);

        // Compute log bounds (use same method as in paint())
        const float logMin = std::log10(std::max(minFreq, 1.0f));
        const float logMax = std::log10(std::max(maxFreq, minFreq + 1.0f));

        for (int i = 0; i < numPoints; ++i) {
                // t in [0..1]
                float t = (float)i / (float)(numPoints - 1);

                // sample frequency uniformly in log space
                float logf = logMin + t * (logMax - logMin);
                float freq = std::pow(10.0f, logf);

                // X position uses the same log mapping as the FFT drawing
                float pos = (logf - logMin) / (logMax - logMin);
                pos = juce::jlimit(0.0f, 1.0f, pos);
                float x = pos * width;

                // magnitude of filter at this frequency
                float magnitude = getFilterMagnitudeForFrequency(freq);

                // avoid zeros when converting to dB
                constexpr float eps = 1e-9f;
                magnitude = std::max(magnitude, eps);

                float magnitudeDB = juce::Decibels::gainToDecibels(magnitude);
                magnitudeDB = juce::jlimit(-60.0f, 12.0f, magnitudeDB);

                // map to Y (same dB -> Y mapping as paint())
                float y = juce::jmap(magnitudeDB, -60.0f, 12.0f, height - 20.0f, 10.0f);

                if (i == 0)
                        filterPath.startNewSubPath(x, y);
                else
                        filterPath.lineTo(x, y);
        }

        g.strokePath(filterPath, juce::PathStrokeType(2.5f));

        // Draw the cutoff marker using the same log mapping
        float clampedCutoff = juce::jlimit(minFreq, maxFreq, currentFilterFreq);
        float cutoffLog = std::log10(std::max(clampedCutoff, 1.0f));
        float cutoffPos = (cutoffLog - logMin) / (logMax - logMin);
        cutoffPos = juce::jlimit(0.0f, 1.0f, cutoffPos);
        int cutoffX = (int)std::round(cutoffPos * width);

        g.setColour(juce::Colours::yellow.withAlpha(0.5f));
        g.drawVerticalLine(cutoffX, 0.0f, height);

        // legend
        g.setColour(juce::Colours::yellow);
        g.setFont(10.0f);
        const char* filterNames[] = { "LowPass", "BandPass", "HighPass" };
        g.drawText(filterNames[currentFilterType], (int)width - 80, 5, 75, 20, juce::Justification::right);
}

float FFTComponent::getFilterMagnitudeForFrequency(float frequency) {
        if (frequency <= 0.0f || currentFilterFreq <= 0.0f || currentSampleRate <= 0.0)
                return 1.0f;

        const float Q = std::max(0.0001f, currentFilterRes);
        const float fc = currentFilterFreq;
        const float fs = (float) currentSampleRate;

        // --- 1) Compute coefficients for cutoff fc ---
        const float omega_c = 2.0f * float(M_PI) * fc / fs;
        const float sin_wc = std::sin(omega_c);
        const float cos_wc = std::cos(omega_c);
        const float alpha = sin_wc / (2.0f * Q);

        float b0 = 1.0f, b1 = 0.0f, b2 = 0.0f;
        float a0 = 1.0f, a1 = 0.0f, a2 = 0.0f;

        switch (currentFilterType) {
                case 0: // Low-pass
                        b0 = (1.0f - cos_wc) * 0.5f;
                        b1 =  1.0f - cos_wc;
                        b2 = (1.0f - cos_wc) * 0.5f;
                        a0 =  1.0f + alpha;
                        a1 = -2.0f * cos_wc;
                        a2 =  1.0f - alpha;
                        break;

                case 1: // Band-pass
                        b0 =  sin_wc * 0.5f;
                        b1 =  0.0f;
                        b2 = -sin_wc * 0.5f;
                        a0 =  1.0f + alpha;
                        a1 = -2.0f * cos_wc;
                        a2 =  1.0f - alpha;
                        break;

                case 2: // High-pass
                        b0 = (1.0f + cos_wc) * 0.5f;
                        b1 = -(1.0f + cos_wc);
                        b2 = (1.0f + cos_wc) * 0.5f;
                        a0 =  1.0f + alpha;
                        a1 = -2.0f * cos_wc;
                        a2 =  1.0f - alpha;
                        break;

                default:
                        return 1.0f;
        }

        // --- 2) Normalize so a0 = 1 ---
        b0 /= a0; b1 /= a0; b2 /= a0;
        a1 /= a0; a2 /= a0;

        // --- 3) Evaluate frequency response at test frequency ---
        const float omega = 2.0f * float(M_PI) * frequency / fs;
        std::complex<float> z1 = std::polar(1.0f, -omega);
        std::complex<float> z2 = std::polar(1.0f, -2.0f * omega);

        std::complex<float> num = b0 + b1 * z1 + b2 * z2;
        std::complex<float> den = std::complex<float>(1.0f, 0.0f) + a1 * z1 + a2 * z2;

        float H = std::abs(num / den);
        return std::max(H, 1e-9f);
}


void FFTComponent::resized() {
}

void FFTComponent::timerCallback() {
        if (nextFFTBlockReady) {
                drawNextFrameOfSpectrum();
                nextFFTBlockReady = false;
                repaint();
        }
}

void FFTComponent::drawNextFrameOfSpectrum() {
        window.multiplyWithWindowingTable(fftData, fftSize);
        forwardFFT.performFrequencyOnlyForwardTransform(fftData);

        auto mindB = -100.0f;
        auto maxdB = 0.0f;

        for (int i = 0; i < fftSize / 2; ++i) {
                float magnitude = fftData[i];
                float db = juce::Decibels::gainToDecibels(magnitude) - juce::Decibels::gainToDecibels((float)fftSize);
                float level = juce::jmap(juce::jlimit(mindB, maxdB, db), mindB, maxdB, 0.0f, 1.0f);

                scopeData[i] = level;
                smoothedScopeData[i] = smoothedScopeData[i] * 0.85f + scopeData[i] * 0.15f;
        }
}

void FFTComponent::pushNextSampleIntoFifo(float sample) noexcept {
        // Si le fifo contient assez de données, définir un drapeau pour dire
        // qu'un bloc FFT peut être rendu.
        if (fifoIndex == fftSize) {
                if (!nextFFTBlockReady) {
                        std::fill(fftData, fftData + fftSize * 2, 0.0f);
                        std::copy(fifo, fifo + fftSize, fftData);
                        nextFFTBlockReady = true;
                }

                fifoIndex = 0;
        }

        fifo[fifoIndex++] = sample;
}

void FFTComponent::updateFilterParams(int filterType, float filterFreq, float filterRes, double sampleRate) {
        currentFilterType = filterType;
        currentFilterFreq = filterFreq;
        currentFilterRes = filterRes;
        currentSampleRate = sampleRate;
}