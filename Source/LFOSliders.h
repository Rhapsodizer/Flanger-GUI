/*
  ==============================================================================

    LFOSliders.h
    Created: 10 May 2022 10:45:37am
    Author:  prude

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LFOSliders  : public juce::Component
{
public:
    LFOSliders();
    ~LFOSliders() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOSliders)

    juce::Slider sweepSlider;
    juce::Label sweepLabel;

    juce::Slider speedSlider;
    juce::Label speedLabel;

    juce::Slider delaySlider;
    juce::Label delayLabel;

    juce::Slider phaseKnob;
    juce::Label phaseLabel;

    juce::Slider feedBackSlider;
    juce::Label feedBackLabel;

public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedBackValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaseValue;
};
