//
// Created by Alex Birch on 01/10/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

class Pill
: public juce::Component
, public juce::Button::Listener
{
public:
    Pill(
        juce::AudioProcessorValueTreeState& valueTreeState,
        int bank,
        bool isFirst,
        bool isLast
    );
    ~Pill();

    void buttonClicked(juce::Button* button) override;

    void resized() override;
    void paint(juce::Graphics& g) override;

    void bankChanged(int bank);
private:

    juce::AudioProcessorValueTreeState& valueTreeState;
    int bank;
    juce::TextButton textButton;

    friend class Pills;
};

class Pills
: public juce::Component
, public juce::ValueTree::Listener
, public juce::AudioProcessorValueTreeState::Listener
{
public:
    Pills(
        juce::AudioProcessorValueTreeState& valueTreeState
    );
    ~Pills();
    
    void cycle(bool right);

    virtual void parameterChanged (const juce::String& parameterID, float newValue) override;

    virtual void valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged,
                                           const juce::Identifier& property) override;
    inline virtual void valueTreeChildAdded (juce::ValueTree& parentTree,
                                             juce::ValueTree& childWhichHasBeenAdded) override {};
    inline virtual void valueTreeChildRemoved (juce::ValueTree& parentTree,
                                               juce::ValueTree& childWhichHasBeenRemoved,
                                               int indexFromWhichChildWasRemoved) override {};
    inline virtual void valueTreeChildOrderChanged (juce::ValueTree& parentTreeWhoseChildrenHaveMoved,
                                                    int oldIndex, int newIndex) override {};
    inline virtual void valueTreeParentChanged (juce::ValueTree& treeWhoseParentHasChanged) override {};
    inline virtual void valueTreeRedirected (juce::ValueTree& treeWhichHasBeenChanged) override {};
private:
    void loadModelFrom(juce::ValueTree& banks);

    juce::AudioProcessorValueTreeState& valueTreeState;

    vector<unique_ptr<Pill>> pills;
    juce::Button *selected;

    void updatePillToggleStates();

    void populate(int initiallySelectedItem);
    void resized() override;
    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pills)
};
