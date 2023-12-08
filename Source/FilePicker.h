//
// Created by Alex Birch on 03/10/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FluidSynthModel.h"

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
    juce::FilenameComponent fileChooser;

    juce::AudioProcessorValueTreeState& valueTreeState;
    // FluidSynthModel& fluidSynthModel;

    juce::String currentPath;

#if JUCE_MAC || JUCE_IOS
    CFURLBookmarkCreationOptions bookmarkCreationOptions;
#endif

    void filenameComponentChanged (juce::FilenameComponent*) override;

    bool shouldChangeDisplayedFilePath(const juce::String &path);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilePicker)
};
