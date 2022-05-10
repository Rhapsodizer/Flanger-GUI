/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LFOSliders.h"

//==============================================================================
/**
*/
class FlangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FlangerAudioProcessorEditor (FlangerAudioProcessor&);
    ~FlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FlangerAudioProcessor& audioProcessor;
    LFOSliders sliders;

    juce::ComboBox waveSelector;
    juce::Label waveSelectorLabel;

    juce::ComboBox interpolSelector;
    juce::Label interpolSelectorLabel;

    juce::ToggleButton phaseSwitch;
    
    juce::Slider wetDrySlider;
    juce::Label wetDryLabel;

    juce::TextButton oscView;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetDrySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment > waveformAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment > interpolationAttachment;
    //void sliderValueChanged(juce::Slider* slider) override;
    //void FlangerAudioProcessorEditor::selectorChanged(juce::ComboBox* selector) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessorEditor)
};