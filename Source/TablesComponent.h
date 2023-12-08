//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Pills.h"
#include "TableComponent.h"
#include "FluidSynthModel.h"

using namespace std;

class TablesComponent : public juce::Component
{
public:
    TablesComponent(
        juce::AudioProcessorValueTreeState& valueTreeState
    );

    void resized() override;

    bool keyPressed(const juce::KeyPress &key) override;

private:
    juce::AudioProcessorValueTreeState& _valueTreeState;

    Pills _banks;
    TableComponent _presetTable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TablesComponent)
};
