//
// Created by Alex Birch on 03/10/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#if JUCE_MAC || JUCE_IOS
//   #include <CoreFoundation/CoreFoundation.h>
  #include <CoreFoundation/CFURL.h>
#endif

class FilePicker: public juce::Component,
                  public juce::ValueTree::Listener,
                  private juce::FilenameComponentListener
{
public:
    FilePicker(
        juce::AudioProcessorValueTreeState& valueTreeState
        // FluidSynthModel& fluidSynthModel
    );
    ~FilePicker();

    void resized() override;
    void paint (juce::Graphics& g) override;

    void setDisplayedFilePath(const juce::String&);
    

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
private:
    juce::FilenameComponent _fileChooser;

    juce::AudioProcessorValueTreeState& _valueTreeState;
    // FluidSynthModel& fluidSynthModel;

    juce::String _currentPath;

#if JUCE_MAC || JUCE_IOS
    CFURLBookmarkCreationOptions bookmarkCreationOptions;
#endif

    void filenameComponentChanged (juce::FilenameComponent*) override;

    bool shouldChangeDisplayedFilePath(const juce::String &path);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilePicker)
};
