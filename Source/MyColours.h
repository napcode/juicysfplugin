//
// Created by Alex Birch on 03/10/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MyColours {
public:
    static juce::Colour getUIColourIfAvailable (juce::LookAndFeel_V4::ColourScheme::UIColour uiColour, juce::Colour fallback);

};