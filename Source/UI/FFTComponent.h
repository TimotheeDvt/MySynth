#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_gui_basics/juce_gui_basics.h>

class FFTComponent : public juce::Component, private juce::Timer {
public:
  FFTComponent();
  ~FFTComponent() override;

  void paint(juce::Graphics&) override;
  void resized() override;

  void pushNextSampleIntoFifo(float sample) noexcept;

  void updateFilterParams(int filterType, float filterFreq, float filterRes, double sampleRate);

private:
  void timerCallback() override;
  void drawNextFrameOfSpectrum();
  void drawFilterCurve(juce::Graphics& g);

  float getFilterMagnitudeForFrequency(float frequency);

  static constexpr auto fftOrder = 12;
  static constexpr auto fftSize = 1 << fftOrder;  // 4096

  juce::dsp::FFT forwardFFT;
  juce::dsp::WindowingFunction<float> window;

  float fifo[fftSize];
  float fftData[2 * fftSize];
  int fifoIndex = 0;
  bool nextFFTBlockReady = false;
  float scopeData[fftSize / 2];

  int currentFilterType = 0;  // 0: LowPass, 1: BandPass, 2: HighPass
  float currentFilterFreq = 2000.0f;
  float currentFilterRes = 1.0f;
  double currentSampleRate = 44100.0;

  static constexpr int smoothingFactor = 3;
  float smoothedScopeData[fftSize / 2];

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FFTComponent)
};