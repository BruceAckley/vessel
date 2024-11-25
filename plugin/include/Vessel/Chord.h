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
    Chord(const juce::String& f, const juce::String& m,
          const juce::String& r, const juce::String& intervalsCSV)
        : function(f), mood(m), region(r)
    {
        parseIntervals(intervalsCSV);
    }

    void setTonalCenter(int tonalCenter, int octave = 3);
    std::vector<int> getMidiNotes() const;
    static const std::map<juce::String, int> chordNameToMidi;
    static const std::map<juce::String, int> functionToMidiOffset;
    std::vector<int> transposedNotes;

private:
    int rootMidiNote = 0;

    void parseIntervals(const juce::String& intervalsCSV);
    void transposeIntervals();
    int getMidiNoteFromFunction(const juce::String& function, int tonalCenter);
};

#endif // CHORD_H
