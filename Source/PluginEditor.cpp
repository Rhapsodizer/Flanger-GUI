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
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor (FlangerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    //LFO Sliderds
    //LFOSliders sliders;
    addAndMakeVisible(sliders);

    // LFO wave form selector
    waveSelector.addItem("Sine wave", 1);
    waveSelector.addItem("Saw wave", 2);
    waveSelector.addItem("Triangular Wave", 3);
    waveSelector.addItem("Square Wave", 4);
    //waveSelector.onChange = [this] { waveSelectorChanged(); };
    waveSelector.setSelectedId(1);
    waveSelectorLabel.setText("LFO Type", juce::dontSendNotification);
    addAndMakeVisible(waveSelectorLabel);
    addAndMakeVisible(waveSelector);
    

    // Interpolation selector
    interpolSelector.addItem("Linear", 1);
    interpolSelector.addItem("Square", 2);
    interpolSelector.addItem("Cubic", 3);
    //interpolSelector.onChange = [this] { interpolSelectorChanged(); };
    interpolSelector.setSelectedId(1);

    interpolSelectorLabel.setText("Interpolation", juce::dontSendNotification);

    addAndMakeVisible(interpolSelector);
    addAndMakeVisible(interpolSelectorLabel);

    // Phase switch
    phaseSwitch.setButtonText("Invert phase");
    addAndMakeVisible(phaseSwitch);

    // WetDry Slider
    // wet = 0, dry = 1
    wetDrySlider.setRange (0.0, 1.0);
    wetDrySlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, 20);
    wetDrySlider.addListener(this);
    wetDryLabel.setText ("Wet/Dry", juce::dontSendNotification);
    addAndMakeVisible(wetDryLabel);
    addAndMakeVisible (wetDrySlider);

    oscView.setColour(juce::TextButton::buttonColourId, juce::Colours::darkmagenta);
    oscView.setButtonText("View OSC");
    addAndMakeVisible(oscView);
    

    // Window size
    // Resizable vertically and horizonally
    setResizable(true, true);
    // min width, min height, max width, max height
    setResizeLimits(GUI_WIDTH * scaleUI / 1.5, GUI_HEIGHT * scaleUI, GUI_WIDTH * scaleUI * 3, GUI_HEIGHT * scaleUI * 3);
    setSize(GUI_WIDTH * scaleUI, GUI_HEIGHT * scaleUI);
}

FlangerAudioProcessorEditor::~FlangerAudioProcessorEditor()
{
}

//==============================================================================
void FlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    // Label colors
    getLookAndFeel().setColour(juce::Label::textColourId, juce::Colours::red);
    g.setColour (juce::Colours::white);
    g.setFont (18.0f);
}

void FlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    juce::FlexBox externalFlex;
    externalFlex.flexWrap = juce::FlexBox::Wrap::wrap;
    externalFlex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    externalFlex.flexDirection = juce::FlexBox::Direction::row;

        juce::FlexBox knobBox;
        knobBox.flexWrap = juce::FlexBox::Wrap::wrap;
        knobBox.justifyContent = juce::FlexBox::JustifyContent::center;
        knobBox.flexDirection = juce::FlexBox::Direction::column;
    
            juce::FlexBox wetDryBox;
            wetDryBox.flexDirection = juce::FlexBox::Direction::column;
            wetDryBox.items.add(juce::FlexItem(wetDryLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(0.2, 1));
            wetDryBox.items.add(juce::FlexItem(wetDrySlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1,1));
            

        knobBox.items.add(juce::FlexItem(sliders).withMinHeight(300.0f).withHeight(350.0f).withFlex(2, 1));                                                 // [4]

        knobBox.items.add(juce::FlexItem(wetDryBox).withFlex(1, 0));
        knobBox.performLayout(getLocalBounds().reduced(10, 16).toFloat());

        juce::FlexBox sideBar;
        sideBar.flexDirection = juce::FlexBox::Direction::column;
        sideBar.justifyContent = juce::FlexBox::JustifyContent::flexStart;
        juce::FlexItem side(200, (float)getHeight(), sideBar);
            juce::FlexBox interpolBox;
            interpolBox.flexDirection = juce::FlexBox::Direction::column;
            interpolBox.items.add(juce::FlexItem(interpolSelectorLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(0,1));
            interpolBox.items.add(juce::FlexItem(interpolSelector).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(0,1));
            interpolBox.performLayout(getLocalBounds().reduced(10, 16).toFloat());

            juce::FlexBox waveBox;
            waveBox.flexDirection = juce::FlexBox::Direction::column;
            waveBox.items.add(juce::FlexItem(waveSelectorLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(0,1));
            waveBox.items.add(juce::FlexItem(waveSelector).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(0,1));
            waveBox.performLayout(getLocalBounds().reduced(10, 16).toFloat());
            
        sideBar.items.add(juce::FlexItem(interpolBox).withFlex(2.5).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1,1, 50.0f));                                                 // [4]
        sideBar.items.add(juce::FlexItem(waveBox).withFlex(2.5).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1, 50.0f));
        sideBar.items.add(juce::FlexItem(phaseSwitch).withFlex(1).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1, 50.0f));
        sideBar.items.add(juce::FlexItem(oscView).withFlex(0.5));
        sideBar.performLayout(getLocalBounds().reduced(10, 16).toFloat());
        //sideBar.items.add(juce::FlexItem(diagnosticLabel).withFlex(2.5).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1, 50.0f));

    externalFlex.items.add(juce::FlexItem(knobBox).withFlex(2.5).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(2, 1));
    externalFlex.items.add(juce::FlexItem(side).withFlex(2.5).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(0,1,150.0f));
    externalFlex.performLayout(getLocalBounds().reduced(10, 16).toFloat());
}

void FlangerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    //setParameter(int index, float newValue)
    if (slider == &wetDrySlider) { audioProcessor.setParameter(3, wetDrySlider.getValue()); }
}

void FlangerAudioProcessorEditor::setDiagnosticLabel(float f) {
    //this.diagnosticLabel.setText();
}