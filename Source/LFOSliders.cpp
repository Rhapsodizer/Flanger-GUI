/*
  ==============================================================================

    LFOSliders.cpp
    Created: 11 May 2022 11:30:14am
    Author:  prude

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOSliders.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LFOSliders::LFOSliders(FlangerAudioProcessor& p): audioProcessor(p)
{
    // LFO Sweep (Amplitude)
    sweepSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    sweepSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    sweepLabel.setText("Sweep", juce::dontSendNotification);

    addAndMakeVisible(sweepSlider);
    addAndMakeVisible(sweepLabel);

    // LFO Speed (Frequency)
    speedSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    speedLabel.setText("Speed", juce::dontSendNotification);

    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);

    // Delay
    delaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    delayLabel.setText("Delay/Amount", juce::dontSendNotification);

    addAndMakeVisible(delaySlider);
    addAndMakeVisible(delayLabel);

    // Feedforward gain
    gSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    gLabel.setText("Depth", juce::dontSendNotification);

    addAndMakeVisible(gSlider);
    addAndMakeVisible(gLabel);

    // Feedback gain
    fbSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    fbSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

    fbLabel.setText("Feedback", juce::dontSendNotification);

    addAndMakeVisible(fbSlider);
    addAndMakeVisible(fbLabel);

    // Parameters
    sweepCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SWEEP", sweepSlider);
    speedCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SPEED", speedSlider);
    delayCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DELAY", delaySlider);
    fbCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FB", fbSlider);
    gCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FF", gSlider);

}

LFOSliders::~LFOSliders()
{
}

void LFOSliders::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::dimgrey);   // clear the background

    // Slider colors
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red);

    g.setColour (juce::Colours::white);
    g.setFont (16.0f);
}

void LFOSliders::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::FlexBox sliderFlex;
    sliderFlex.flexWrap = juce::FlexBox::Wrap::wrap;
    sliderFlex.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    sliderFlex.flexDirection = juce::FlexBox::Direction::column;

    sliderFlex.items.add(juce::FlexItem(sweepLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(80.0f).withFlex(1, 1));
    sliderFlex.items.add(juce::FlexItem(sweepSlider).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sliderFlex.items.add(juce::FlexItem(speedLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(80.0f).withFlex(1, 1));
    sliderFlex.items.add(juce::FlexItem(speedSlider).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sliderFlex.items.add(juce::FlexItem(delayLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(80.0f).withFlex(1, 1));
    sliderFlex.items.add(juce::FlexItem(delaySlider).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sliderFlex.items.add(juce::FlexItem(gLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(80.0f).withFlex(1, 1));
    sliderFlex.items.add(juce::FlexItem(gSlider).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sliderFlex.items.add(juce::FlexItem(fbLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(80.0f).withFlex(1, 1));
    sliderFlex.items.add(juce::FlexItem(fbSlider).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sliderFlex.performLayout(getLocalBounds().reduced(4, 4).toFloat());
}
