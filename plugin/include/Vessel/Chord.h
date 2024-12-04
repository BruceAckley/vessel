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
    int rootNoteOffset;

    Chord() = default;
    Chord(const juce::String& f, const juce::String& m,
          const juce::String& r, const juce::String& intervalsCSV, const int root)
        : function(f), mood(m), region(r), rootNoteOffset(root)
    {
        parseIntervals(intervalsCSV);
    }

    void setTonalCenter(int tonalCenter, int octave = 3);
    static const std::map<juce::String, int> chordNameToMidi;
    static const std::map<juce::String, int> functionToMidiOffset;
    std::vector<int> transposedNotes;

private:
    void parseIntervals(const juce::String& intervalsCSV);
    void transposeIntervals(int rootMidiNote);
};

#endif // CHORD_H
