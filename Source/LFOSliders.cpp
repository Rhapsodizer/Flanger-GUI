/*
  ==============================================================================

    LFOSliders.cpp
    Created: 10 May 2022 10:45:37am
    Author:  xorgol

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOSliders.h"

//==============================================================================
LFOSliders::LFOSliders()
{
    // LFO Sweep (Amplitude)
    sweepSlider.setRange(0.0, 50.0);
    sweepSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    sweepLabel.setText("LFO Amplitude", juce::dontSendNotification);
    addAndMakeVisible(sweepLabel);
    addAndMakeVisible(sweepSlider);

    // LFO Speed (Frequency)
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    speedLabel.setText("LFO frequency", juce::dontSendNotification);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(speedSlider);

    // Phase
    phaseKnob.setRange((double)-3.14, (double)3.14);
    phaseKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    phaseLabel.setText("LFO Phase", juce::dontSendNotification);
    addAndMakeVisible(phaseKnob);
    addAndMakeVisible(phaseLabel);

    feedBackSlider.setRange(0.0, 10.0);
    feedBackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    feedBackLabel.setText("Feedback Gain", juce::dontSendNotification);
    addAndMakeVisible(feedBackLabel);
    addAndMakeVisible(feedBackSlider);
    

}

LFOSliders::~LFOSliders()
{
}

void LFOSliders::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colour::fromRGB(100, 100, 100));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

     // Slider colors
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red);
    //getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::pink);

    // Label colors
    getLookAndFeel().setColour(juce::Label::textColourId, juce::Colours::white);

    g.setColour (juce::Colours::white);
    g.setFont (18.0f);
    //g.drawText ("LFOSliders", getLocalBounds(),juce::Justification::centred, true);   // draw some placeholder text
}

void LFOSliders::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::FlexBox externalFlex;
    externalFlex.flexWrap = juce::FlexBox::Wrap::wrap;
    externalFlex.justifyContent = juce::FlexBox::JustifyContent::center;
    externalFlex.flexDirection = juce::FlexBox::Direction::column;
    


    juce::FlexBox sweepBox;
    sweepBox.flexDirection = juce::FlexBox::Direction::column;
    sweepBox.items.add(juce::FlexItem(sweepLabel).withMinHeight(20.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(0.5));
    sweepBox.items.add(juce::FlexItem(sweepSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    sweepBox.performLayout(getLocalBounds().reduced(4, 8).toFloat());

    juce::FlexBox speedBox;
    speedBox.flexDirection = juce::FlexBox::Direction::column;
    speedBox.items.add(juce::FlexItem(speedLabel).withMinHeight(20.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(0.5));
    speedBox.items.add(juce::FlexItem(speedSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    speedBox.performLayout(getLocalBounds().reduced(4, 8).toFloat());

    juce::FlexBox phaseBox;
    phaseBox.flexDirection = juce::FlexBox::Direction::column;
    phaseBox.items.add(juce::FlexItem(phaseLabel).withMinHeight(20.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(0.5));
    phaseBox.items.add(juce::FlexItem(phaseKnob).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    phaseBox.performLayout(getLocalBounds().reduced(4, 8).toFloat());

    juce::FlexBox feedBackBox;
    feedBackBox.flexDirection = juce::FlexBox::Direction::column;
    feedBackBox.items.add(juce::FlexItem(feedBackLabel).withMinHeight(20.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(0.5));
    feedBackBox.items.add(juce::FlexItem(feedBackSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    feedBackBox.performLayout(getLocalBounds().reduced(4, 8).toFloat());

    externalFlex.items.add(juce::FlexItem(sweepBox).withFlex(1, 0));
    externalFlex.items.add(juce::FlexItem(speedBox).withFlex(1, 0));
    externalFlex.items.add(juce::FlexItem(phaseBox).withFlex(1, 0));
    externalFlex.items.add(juce::FlexItem(feedBackBox).withFlex(1, 0));
    externalFlex.performLayout(getLocalBounds().reduced(4, 8).toFloat());
}
