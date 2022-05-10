/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FlangerAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    FlangerAudioProcessorEditor(FlangerAudioProcessor&);
    ~FlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FlangerAudioProcessor& audioProcessor;

    //juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    juce::Slider sweepSlider;
    juce::Label sweepLabel;

    juce::Slider speedSlider;
    juce::Label speedLabel;

    juce::Slider delaySlider;
    juce::Label delayLabel;

    juce::Slider fbSlider;
    juce::Label fbLabel;

    juce::ComboBox waveSelector;
    juce::Label waveSelectorLabel;

    juce::ComboBox interpolSelector;
    juce::Label interpolSelectorLabel;

    juce::ToggleButton phaseSwitch;

    juce::Slider wetDrySlider;
    juce::Label wetDryLabel;

    juce::Slider gSlider;
    juce::Label gLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fbCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectorCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> interpolSelectorCall;

    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlangerAudioProcessorEditor)
};
