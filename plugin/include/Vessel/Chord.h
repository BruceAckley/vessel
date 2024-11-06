#ifndef CHORD_H
#define CHORD_H

#include <juce_core/juce_core.h>
#include <vector>
#include <map>

class Chord {
public:
    juce::String name;
    juce::String function;
    juce::String mood;
    juce::String region;
    std::vector<int> intervalPattern;

    Chord() = default;
    Chord(const juce::String& function, const juce::String& mood,
          const juce::String& region, const juce::String& intervalsCSV)
        : function(function), mood(mood), region(region)
    {
        parseIntervals(intervalsCSV);
    }

    void setTonalCenter(const juce::String& tonalCenter, int octave = 3);
    std::vector<int> getMidiNotes() const;

private:
    int rootMidiNote = 0;
    std::vector<int> transposedNotes;

    void parseIntervals(const juce::String& intervalsCSV);
    void transposeIntervals();

    // Declaration only
    static const std::map<juce::String, int> noteMap;
};

#endif // CHORD_H
