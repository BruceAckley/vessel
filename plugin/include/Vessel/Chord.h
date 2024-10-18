#ifndef CHORD_H
#define CHORD_H

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>

class Chord {
public:
    juce::String function;
    juce::String notes_rel_c3;
    juce::String scale;
    juce::String region;

    Chord() = default;
    Chord(const juce::String& f, const juce::String& n, const juce::String& s, const juce::String& r)
        : function(f), notes_rel_c3(n), scale(s), region(r) {}

    std::vector<int> getNotes(juce::String& tonalCenter) {
        std::vector<int> notes;
        juce::StringArray noteStrings;
        noteStrings.addTokens(notes_rel_c3, " ", "");
        for (const auto& note : noteStrings) {
            notes.push_back(getMidiFromNote(note, tonalCenter));
        }
        return notes;
    }

private:
    int getMidiFromNote(const juce::String& note, juce::String& tonalCenter) {
        static const std::map<juce::String, int> noteMap = {
            {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
            {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
        };

        if (note.length() < 2 || note.length() > 3) {
            throw std::invalid_argument("Invalid note name");
        }

        juce::String noteName = note.dropLastCharacters(1);
        int octave = note.getLastCharacter() - '0';

        if (noteMap.find(noteName) == noteMap.end() || octave < 0 || octave > 9) {
            throw std::invalid_argument("Invalid note name");
        }

        if (noteMap.find(tonalCenter) == noteMap.end()) {
            throw std::invalid_argument("Invalid tonal center");
        }

        return noteMap.at(noteName) + ((octave + 1) * 12) + noteMap.at(tonalCenter);
    }
};

#endif // CHORD_H
