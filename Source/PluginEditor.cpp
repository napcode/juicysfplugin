/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "GuiConstants.h"

using namespace juce;

//==============================================================================
JuicySFAudioProcessorEditor::JuicySFAudioProcessorEditor(
    JuicySFAudioProcessor& p,
    AudioProcessorValueTreeState& valueTreeState)
: AudioProcessorEditor{&p}
, _processor{p}
, _valueTreeState{valueTreeState}
, _midiKeyboard{p.keyboardState, SurjectiveMidiKeyboardComponent::horizontalKeyboard}
, _tablesComponent{valueTreeState}
, _filePicker{valueTreeState}
, _slidersComponent{valueTreeState, p.getFluidSynthModel()}
{
    // set resize limits for this plug-in
    setResizeLimits(
        GuiConstants::minWidth,
        GuiConstants::minHeight,
        GuiConstants::maxWidth,
        GuiConstants::maxHeight);

    _lastUIWidth.referTo(valueTreeState.state.getChildWithName("uiState").getPropertyAsValue("width",  nullptr));
    _lastUIHeight.referTo(valueTreeState.state.getChildWithName("uiState").getPropertyAsValue("height", nullptr));

    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize(_lastUIWidth.getValue(), _lastUIHeight.getValue());

    _lastUIWidth.addListener(this);
    _lastUIHeight.addListener(this);

    _midiKeyboard.setName ("MIDI Keyboard");

    _midiKeyboard.setWantsKeyboardFocus(false);
    _tablesComponent.setWantsKeyboardFocus(false);

    setWantsKeyboardFocus(true);
    addAndMakeVisible(_midiKeyboard);

    addAndMakeVisible(_slidersComponent);
    addAndMakeVisible(_tablesComponent);
    addAndMakeVisible(_filePicker);

}

// called when the stored window size changes
void JuicySFAudioProcessorEditor::valueChanged(Value&) {
    setSize(_lastUIWidth.getValue(), _lastUIHeight.getValue());
}

JuicySFAudioProcessorEditor::~JuicySFAudioProcessorEditor()
{
    _lastUIWidth.removeListener(this);
    _lastUIHeight.removeListener(this);
}

//==============================================================================
void JuicySFAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    if (!_focusInitialized) {
        if (!hasKeyboardFocus(false) && isVisible()) {
            grabKeyboardFocus();
        }
        if (getCurrentlyFocusedComponent() == this) {
            _focusInitialized = true;
        }
    }
}

void JuicySFAudioProcessorEditor::resized()
{
    const int padding{8};
    const int pianoHeight{70};
    const int filePickerHeight{25};
    Rectangle<int> r{getLocalBounds()};
    _filePicker.setBounds(r.removeFromTop(filePickerHeight + padding).reduced(padding, 0).withTrimmedTop(padding));

    _midiKeyboard.setBounds (r.removeFromBottom (pianoHeight).reduced(padding, 0));

    Rectangle<int> rContent{r.reduced(0, padding)};
    _slidersComponent.setBounds(rContent.removeFromRight(_slidersComponent.getDesiredWidth() + padding).withTrimmedRight(padding));

    _tablesComponent.setBounds(rContent);

    _lastUIWidth = getWidth();
    _lastUIHeight = getHeight();
}

bool JuicySFAudioProcessorEditor::keyPressed(const KeyPress &key) {
    const int cursorKeys[] = {
            KeyPress::leftKey,
            KeyPress::rightKey,
            KeyPress::upKey,
            KeyPress::downKey
    };
    if (any_of(
            begin(cursorKeys),
            end(cursorKeys),
            [&](int i) { return i == key.getKeyCode(); }
    )) {
        return _tablesComponent.keyPressed(key);
    } else {
        return _midiKeyboard.keyPressed(key);
    }
    return false;
}

bool JuicySFAudioProcessorEditor::keyStateChanged (bool isKeyDown) {
    return _midiKeyboard.keyStateChanged(isKeyDown);
}
