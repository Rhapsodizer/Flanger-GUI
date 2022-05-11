/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


const int GUI_WIDTH = 800;
const int GUI_HEIGHT = 720;
float scaleUI = 1.0f;  // this can be 0.5, 0.666 or 1.0

//==============================================================================
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor(FlangerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
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

    // LFO wave form selector
    waveSelector.addItem("Sin", 1);
    waveSelector.addItem("Tri", 2);
    waveSelector.addItem("Sqr", 3);
    waveSelector.addItem("Saw", 4);
    waveSelector.setSelectedId(1);

    waveSelectorLabel.setText("LFO Type", juce::dontSendNotification);

    addAndMakeVisible(waveSelector);
    addAndMakeVisible(waveSelectorLabel);

    // Interpolation selector
    interpolSelector.addItem("Lin", 1);
    interpolSelector.addItem("Sqr", 2);
    interpolSelector.addItem("Cub", 3);
    interpolSelector.setSelectedId(1);

    interpolSelectorLabel.setText("Interpolation", juce::dontSendNotification);

    addAndMakeVisible(interpolSelector);
    addAndMakeVisible(interpolSelectorLabel);

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

    // Phase switch
    phaseSwitch.setButtonText("Invert phase");

    addAndMakeVisible(phaseSwitch);


    // WetDry Slider
    // wet = 0, dry = 1
    wetDrySlider.setRange(0.0, 1.0);
    //wetDrySlider.setValue(1.0);
    wetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    wetDryLabel.setText("Wet/Dry", juce::dontSendNotification);

    addAndMakeVisible(wetDrySlider);
    addAndMakeVisible(wetDryLabel);

    // Window size
    // Resizable vertically and horizonally
    setResizable(true, true);
    // min width, min height, max width, max height
    setResizeLimits(GUI_WIDTH * scaleUI / 1.5, GUI_HEIGHT * scaleUI, GUI_WIDTH * scaleUI * 3, GUI_HEIGHT * scaleUI * 3);
    setSize(GUI_WIDTH * scaleUI, GUI_HEIGHT * scaleUI);

    // Parameters
    sweepCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SWEEP", sweepSlider);
    speedCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SPEED", speedSlider);
    delayCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DELAY", delaySlider);
    fbCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FB", fbSlider);
    gCall = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FF", gSlider);
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

    //g.fillRect(200, 100, 400, 150);
    //g.drawText("This should be an audio visualiser:", 200, 70, 400, 20, juce::Justification::centred, true);

    // Slider colors
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::pink);

    // Label colors
    getLookAndFeel().setColour(juce::Label::textColourId, juce::Colours::pink);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

void FlangerAudioProcessorEditor::resized()
{
    // Component layout
    juce::FlexBox externalFlex;
    externalFlex.flexWrap = juce::FlexBox::Wrap::wrap;
    externalFlex.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    externalFlex.flexDirection = juce::FlexBox::Direction::row;

    juce::FlexBox sliderBox;
    sliderBox.flexWrap = juce::FlexBox::Wrap::wrap;
    sliderBox.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    sliderBox.flexDirection = juce::FlexBox::Direction::column;

    sliderBox.items.add(juce::FlexItem(sweepLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    sliderBox.items.add(juce::FlexItem(sweepSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));

    sliderBox.items.add(juce::FlexItem(speedLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    sliderBox.items.add(juce::FlexItem(speedSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));

    sliderBox.items.add(juce::FlexItem(delayLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    sliderBox.items.add(juce::FlexItem(delaySlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));

    sliderBox.items.add(juce::FlexItem(fbLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    sliderBox.items.add(juce::FlexItem(fbSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    
    sliderBox.items.add(juce::FlexItem(gLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    sliderBox.items.add(juce::FlexItem(gSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    
    sliderBox.items.add(juce::FlexItem(wetDryLabel).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));
    sliderBox.items.add(juce::FlexItem(wetDrySlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1, 1));

    sliderBox.performLayout(getLocalBounds().reduced(10, 16).toFloat());
    
    juce::FlexBox sideBar;
    sideBar.flexWrap = juce::FlexBox::Wrap::wrap;
    sideBar.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    sideBar.flexDirection = juce::FlexBox::Direction::column;

    sideBar.items.add(juce::FlexItem(waveSelectorLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(120.0f).withFlex(1, 1));
    sideBar.items.add(juce::FlexItem(waveSelector).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(120.0f).withFlex(1, 1));

    sideBar.items.add(juce::FlexItem(interpolSelectorLabel).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(120.0f).withFlex(1, 1));
    sideBar.items.add(juce::FlexItem(interpolSelector).withMinHeight(50.0f).withMinWidth(50.0f).withMaxHeight(120.0f).withFlex(1, 1));

    sideBar.items.add(juce::FlexItem(phaseSwitch).withMinHeight(50.0f).withMinWidth(80.0f).withFlex(1, 1));
    sideBar.performLayout(getLocalBounds().reduced(10, 16).toFloat());

    externalFlex.items.add(juce::FlexItem(sliderBox).withFlex(5, 0));
    externalFlex.items.add(juce::FlexItem(sideBar).withFlex(1, 0));
    externalFlex.performLayout(getLocalBounds().reduced(10, 16).toFloat());

}
