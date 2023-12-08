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

    int _preset;
    juce::String _name;
    
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
    void loadModelFrom(juce::ValueTree& banks);
    void repopulateTable();
    void selectCurrentPreset();

    juce::AudioProcessorValueTreeState& _valueTreeState;

    juce::TableListBox _table;     // the table component itself
    juce::Font _font;

    typedef multimap<int, TableRow> BanksToPresets;
    BanksToPresets _banksToPresets;

    vector<TableRow> _rows;

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
        int _columnByWhichToSort;
        int _direction;
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TableComponent)
};
