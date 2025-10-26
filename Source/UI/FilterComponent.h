#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class FilterComponent  : public juce::Component {
public:
  FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
  ~FilterComponent() override;

  void paint (juce::Graphics&) override;
  void resized() override;

private:
  using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

  juce::ComboBox filterTypeSelector { "Filter Type" };
  juce::Slider filterFreqSlider;
  juce::Slider filterResSlider;

  juce::Label filterFreqLabel { "FILTERFREQLABEL", "Filter Freq" };
  juce::Label filterResLabel { "FILTERRESLABEL", "Filter Res"};

  std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
  std::unique_ptr<SliderAttachment> filterFreqAttachment;
  std::unique_ptr<SliderAttachment> filterResAttachment;

  void setSliderLabel (juce::Slider& slider, juce::Label& label,
      std::unique_ptr<SliderAttachment>& attachment,
      juce::AudioProcessorValueTreeState& apvts, juce::String paramId);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
