/*
  ==============================================================================

    LFOSliders.h
    Created: 11 May 2022 11:30:14am
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
};
