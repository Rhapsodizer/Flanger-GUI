/*
  ==============================================================================

    LFOSliders.h
    Created: 11 May 2022 11:30:14am
    Author:  prude

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LFOSliders  : public juce::Component
{
public:
    LFOSliders(FlangerAudioProcessor& p);
    ~LFOSliders() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOSliders)

    FlangerAudioProcessor& audioProcessor;

    juce::Slider sweepSlider;
    juce::Label sweepLabel;

    juce::Slider speedSlider;
    juce::Label speedLabel;

    juce::Slider delaySlider;
    juce::Label delayLabel;

    juce::Slider fbSlider;
    juce::Label fbLabel;

    juce::Slider wetDrySlider;
    juce::Label wetDryLabel;

    juce::Slider gSlider;
    juce::Label gLabel;

public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fbCall;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gCall;
};
