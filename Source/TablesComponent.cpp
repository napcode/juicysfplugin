//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"
#include <memory>
#include <fluidsynth.h>

using namespace juce;
using namespace std;
using namespace placeholders;

TablesComponent::TablesComponent(
    AudioProcessorValueTreeState& valueTreeState
)
: _valueTreeState{valueTreeState}
, _banks{valueTreeState}
, _presetTable{valueTreeState}
{

    _presetTable.setWantsKeyboardFocus(false);

    addAndMakeVisible(_presetTable);

    addAndMakeVisible(_banks);
}

void TablesComponent::resized() {
    Rectangle<int> r (getLocalBounds());
    _banks.setBounds (r.removeFromTop(27).reduced(5,0));

    _presetTable.setBounds (r);
}

bool TablesComponent::keyPressed(const KeyPress &key) {
    if (key.getKeyCode() == KeyPress::leftKey
            || key.getKeyCode() == KeyPress::rightKey) {
        _banks.cycle(key.getKeyCode() == KeyPress::rightKey);
        return true;
    }
    return _presetTable.keyPressed(key);
}
