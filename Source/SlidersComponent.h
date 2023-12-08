# pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FluidSynthModel.h"

using namespace std;
using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

class SlidersComponent : public juce::Component
{
public:
    SlidersComponent(
        juce::AudioProcessorValueTreeState& valueTreeState,
        FluidSynthModel& fluidSynthModel);
    ~SlidersComponent();

    void resized() override;

    const int getDesiredWidth();

    void acceptMidiControlEvent(int controller, int value);

private:
    std::function<void()> makeSliderListener(juce::Slider& slider, int controller);

    juce::AudioProcessorValueTreeState& valueTreeState;
    FluidSynthModel& fluidSynthModel;

    juce::GroupComponent envelopeGroup;

    juce::Slider attackSlider;
    juce::Label attackLabel;
    unique_ptr<SliderAttachment> attackSliderAttachment;

    juce::Slider decaySlider;
    juce::Label decayLabel;
    unique_ptr<SliderAttachment> decaySliderAttachment;

    juce::Slider sustainSlider;
    juce::Label sustainLabel;
    unique_ptr<SliderAttachment> sustainSliderAttachment;

    juce::Slider releaseSlider;
    juce::Label releaseLabel;
    unique_ptr<SliderAttachment> releaseSliderAttachment;

    juce::GroupComponent filterGroup;

    juce::Slider filterCutOffSlider;
    juce::Label filterCutOffLabel;
    unique_ptr<SliderAttachment> filterCutOffSliderAttachment;

    juce::Slider filterResonanceSlider;
    juce::Label filterResonanceLabel;
    unique_ptr<SliderAttachment> filterResonanceSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SlidersComponent)
};
