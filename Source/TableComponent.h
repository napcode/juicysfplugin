//
//  Model.hpp
//  Lazarus
//
//  Created by Alex Birch on 01/09/2017.
//
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <memory>
#include <string>
#include <map>

using namespace std;

class TableRow {
public:
    TableRow(
             int preset,
             juce::String name
             );
private:
    /** 1-indexed */
    juce::String getStringContents(int columnId);

    int preset;
    juce::String name;
    
    friend class TableComponent;
};


class TableComponent    : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::ValueTree::Listener,
                          public juce::AudioProcessorValueTreeState::Listener {
public:
    TableComponent(
            juce::AudioProcessorValueTreeState& valueTreeState
    );
    ~TableComponent();

    int getNumRows() override;

    void paintRowBackground (
            juce::Graphics& g,
            int rowNumber,
            int width,
            int height,
            bool rowIsSelected
    ) override;
    void paintCell (
            juce::Graphics& g,
            int rowNumber,
            int columnId,
            int width,
            int height,
            bool rowIsSelected
    ) override;

    void sortOrderChanged (int newSortColumnId, bool isForwards) override;

    int getColumnAutoSizeWidth (int columnId) override;

    void selectedRowsChanged (int row) override;

    void resized() override;

    bool keyPressed(const juce::KeyPress &key) override;

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
    void repopulateTable();
    void selectCurrentPreset();

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::TableListBox table;     // the table component itself
    juce::Font font;

    typedef multimap<int, TableRow> BanksToPresets;
    BanksToPresets banksToPresets;

    vector<TableRow> rows;

    // A comparator used to sort our data when the user clicks a column header
    class DataSorter {
    public:
        DataSorter (
                int columnByWhichToSort,
                bool forwards
        );

        bool operator ()(
                TableRow first,
                TableRow second
        );

    private:
        int columnByWhichToSort;
        int direction;
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TableComponent)
};
