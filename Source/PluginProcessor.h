/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#if JUCE_MAC || JUCE_IOS
  #include <Foundation/NSString.h>
  #include <Foundation/NSArray.h>
#endif
#include "../JuceLibraryCode/JuceHeader.h"
#include "FluidSynthModel.h"
#include <list>

using namespace std;

//==============================================================================
/**
*/
class JuicySFAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    JuicySFAudioProcessor();
    ~JuicySFAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    bool supportsDoublePrecisionProcessing() const override;

    FluidSynthModel& getFluidSynthModel();

    juce::MidiKeyboardState keyboardState;

private:
    void initialiseSynth();

    juce::AudioProcessorValueTreeState valueTreeState;

    FluidSynthModel fluidSynthModel;
    juce::Synthesiser synth;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    static BusesProperties getBusesProperties();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuicySFAudioProcessor)
};
