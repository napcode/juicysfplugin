//
// Created by Alex Birch on 10/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <fluidsynth.h>
#include <memory>
#include <map>
#include "MidiConstants.h"

using namespace std;

class FluidSynthModel
: public juce::ValueTree::Listener
, public juce::AudioProcessorValueTreeState::Listener {
public:
    FluidSynthModel(
        juce::AudioProcessorValueTreeState& valueTreeState
        );
     ~FluidSynthModel();

    void initialise();
    
    int getChannel();

    void setControllerValue(int controller, int value);

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);


    void setSampleRate(float sampleRate);
    
    //==============================================================================
    virtual void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    virtual void valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged,
                                           const juce::Identifier& property) override;
    inline virtual void valueTreeChildAdded ([[maybe_unused]] juce::ValueTree& parentTree,
                                             [[maybe_unused]] juce::ValueTree& childWhichHasBeenAdded) override {};
    inline virtual void valueTreeChildRemoved ([[maybe_unused]] juce::ValueTree& parentTree,
                                               [[maybe_unused]] juce::ValueTree& childWhichHasBeenRemoved,
                                               [[maybe_unused]] int indexFromWhichChildWasRemoved) override {};
    inline virtual void valueTreeChildOrderChanged ([[maybe_unused]] juce::ValueTree& parentTreeWhoseChildrenHaveMoved,
                                                    [[maybe_unused]] int oldIndex, [[maybe_unused]] int newIndex) override {};
    inline virtual void valueTreeParentChanged ([[maybe_unused]] juce::ValueTree& treeWhoseParentHasChanged) override {};
    inline virtual void valueTreeRedirected ([[maybe_unused]] juce::ValueTree& treeWhichHasBeenChanged) override {};

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram(int index);
    const juce::String getProgramName(int index);
    void changeProgramName(int index, const juce::String& newName);

private:
    static const juce::StringArray _programChangeParams;

    // there's no bimap in the standard library!
    static const map<fluid_midi_control_change, juce::String> _controllerToParam;
    static const map<juce::String, fluid_midi_control_change> _paramToController;

    void refreshBanks();

    juce::AudioProcessorValueTreeState& _valueTreeState;

    // https://stackoverflow.com/questions/38980315/is-stdunique-ptr-deletion-order-guaranteed
    // members are destroyed in reverse of the order they're declared
    // http://www.fluidsynth.org/api/
    // in their examples, they destroy the synth before destroying the settings
    unique_ptr<fluid_settings_t, decltype(&delete_fluid_settings)> _settings;
    unique_ptr<fluid_synth_t, decltype(&delete_fluid_synth)> _synth;

    float _currentSampleRate;

    void unloadAndLoadFont(const juce::String &absPath);
    void loadFont(const juce::String &absPath);
    
    int _sfont_id;
    int _channel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FluidSynthModel)
};
