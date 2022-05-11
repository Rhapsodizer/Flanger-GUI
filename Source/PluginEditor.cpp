/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LFOSliders.h"


const int GUI_WIDTH = 800;
const int GUI_HEIGHT = 720;
float scaleUI = 1.0f;  // this can be 0.5, 0.666 or 1.0

//==============================================================================
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor(FlangerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), sliders(p)
{
    addAndMakeVisible(sliders);

    // LFO wave form selector
    waveSelector.addItem("Sine", 1);
    waveSelector.addItem("Triangular", 2);
    waveSelector.addItem("Square", 3);
    waveSelector.addItem("Saw", 4);
    waveSelector.setSelectedId(1);

    waveSelectorLabel.setText("LFO Type", juce::dontSendNotification);

    addAndMakeVisible(waveSelector);
    addAndMakeVisible(waveSelectorLabel);

    // Interpolation selector
    interpolSelector.addItem("Linear", 1);
    interpolSelector.addItem("Quadratic", 2);
    interpolSelector.addItem("Cubic", 3);
    interpolSelector.setSelectedId(1);

    interpolSelectorLabel.setText("Interpolation", juce::dontSendNotification);

    addAndMakeVisible(interpolSelector);
    addAndMakeVisible(interpolSelectorLabel);

    // Phase switch
    phaseSwitch.setButtonText("Invert phase");
    addAndMakeVisible(phaseSwitch);


    // Window size
    // Resizable vertically and horizonally
    setResizable(true, true);
    // min width, min height, max width, max height
    setResizeLimits(GUI_WIDTH * scaleUI / 2, GUI_HEIGHT * scaleUI / 1.3, GUI_WIDTH * scaleUI * 3, GUI_HEIGHT * scaleUI * 3);
    setSize(GUI_WIDTH * scaleUI, GUI_HEIGHT * scaleUI);

    // Parameters

    waveSelectorCall = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "WAVE", waveSelector);
    interpolSelectorCall = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "INTERPOL", interpolSelector);


}

FlangerAudioProcessorEditor::~FlangerAudioProcessorEditor()
{
}

//==============================================================================
void FlangerAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // Label colors
    getLookAndFeel().setColour(juce::Label::textColourId, juce::Colours::white);

    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
}

void FlangerAudioProcessorEditor::resized()
{
    // Component layout
    juce::FlexBox externalFlex;
    externalFlex.flexWrap = juce::FlexBox::Wrap::wrap;
    externalFlex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    externalFlex.flexDirection = juce::FlexBox::Direction::row;


    
    juce::FlexBox sideBar;
    sideBar.flexWrap = juce::FlexBox::Wrap::wrap;
    sideBar.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    sideBar.flexDirection = juce::FlexBox::Direction::column;
    juce::FlexBox bottomSpace;

    sideBar.items.add(juce::FlexItem(waveSelectorLabel).withMinHeight(50.0f).withMinWidth(80.0f).withMaxHeight(50.0f).withFlex(0.5, 1));
    sideBar.items.add(juce::FlexItem(waveSelector).withMinHeight(50.0f).withMinWidth(80.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sideBar.items.add(juce::FlexItem(interpolSelectorLabel).withMinHeight(50.0f).withMinWidth(80.0f).withMaxHeight(50.0f).withFlex(0.5, 1));
    sideBar.items.add(juce::FlexItem(interpolSelector).withMinHeight(50.0f).withMinWidth(80.0f).withMaxHeight(50.0f).withFlex(1, 1));

    sideBar.items.add(juce::FlexItem(phaseSwitch).withMinHeight(50.0f).withMinWidth(80.0f).withFlex(1, 1));
    sideBar.items.add(juce::FlexItem(bottomSpace).withMinHeight(50.0f).withFlex(5, 1));
    sideBar.performLayout(getLocalBounds().reduced(16, 16).toFloat());

    externalFlex.items.add(juce::FlexItem(sliders).withFlex(5, 0));
    externalFlex.items.add(juce::FlexItem(sideBar).withFlex(1, 0));
    externalFlex.performLayout(getLocalBounds().reduced(4, 8).toFloat());

}
